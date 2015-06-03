 // compile: sudo gcc -std=c99 gpiotest.c -o gpiotest.exe -l bcm2835 -pthread
// version 0.1 master
#include <bcm2835.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h> 
#define MOUSEFILE "/dev/input/event1"

#define PIN1 RPI_V2_GPIO_P1_12
#define PIN2 RPI_V2_GPIO_P1_16
#define PIN3 RPI_V2_GPIO_P1_18
#define PIN4 RPI_V2_GPIO_P1_22
/*
#define PIN5 RPI_V2_GPIO_P1_07
#define PIN6 RPI_V2_GPIO_P1_11
#define PIN7 RPI_V2_GPIO_P1_15
*/

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *mouseListener();
void *tableRotator();
//void prepareStep(char *s[], int steps, int counter);
void makeStep(char *ws);

int mouseStateFlag=0;

int main() {
    pthread_t mouseThread, tableThread;
    int mouseThreadError, tableThreadError;
    
    if ( !bcm2835_init() ) {
        return 1;
    }
    
    mouseThreadError = pthread_create(&mouseThread, NULL, mouseListener, NULL);
    if( mouseThreadError ) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", mouseThreadError);
        exit(EXIT_FAILURE);
    }
    
    tableThreadError = pthread_create(&tableThread, NULL, tableRotator, NULL);
    if( tableThreadError ) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", tableThreadError);
        exit(EXIT_FAILURE);
    }
    pthread_join( mouseThread, NULL);
    pthread_join( tableThread, NULL);
    
    bcm2835_close();
    
    return 0;
}

void *mouseListener() {
    int fd;
    struct input_event ie;
    
    if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("opening device");
        exit(EXIT_FAILURE);
    }
    while(read(fd, &ie, sizeof(struct input_event))) {
        while ( ie.type != 274 ) {
            printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", 
                   ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
            if (ie.type == 272 || ie.type == 273) {
                if ( mouseStateFlag == 0 ) {
                    pthread_mutex_lock(&mutex1);
                    mouseStateFlag = ie.type;
                    pthread_mutex_unlock(&mutex1);
                }
            }
        }
        pthread_mutex_lock(&mutex1);
        mouseStateFlag = ie.type;
        pthread_mutex_unlock(&mutex1);
        return;
    }
}

void *tableRotator() {
    int i;
    char* steps4[4];
    //char* steps8[8];
    //char* workingSteps;
    char *blankString = "0 0 0 0";
    
    steps4[0] = "1 0 0 1";
    steps4[1] = "0 1 0 1";
    steps4[2] = "0 1 1 0";
    steps4[3] = "1 0 1 0";
    
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
    
    while ( mouseStateFlag != 274 ) {
        if (mouseStateFlag == 272 || mouseStateFlag == 273 ) {
            makeStep(blankString);
            for (int i = 0; i < 4; i++ ) {
                makeStep(steps4[i]);
            }
            makeStep(blankString);
        }
        pthread_mutex_lock(&mutex1);
        mouseStateFlag = 0;
        pthread_mutex_unlock(&mutex1);
    } 
}

/*
 * void prepareStep(char *s[], int scale, int counter) {
    
    //uint8_t valueOnSix, valueOnSeven;
    //char flagButtonRelease = 1;
    
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);

    попробуем без кнопок. управляем мышкой.
    bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_write(PIN5, HIGH);
    bcm2835_gpio_write(PIN6, LOW);
    bcm2835_gpio_write(PIN7, LOW);
}
*/

void makeStep(char *ws) {
    int a[4];
    for ( int i = 0; i < 4 && *ws != '\0'; ) {
        if ( *ws != ' ' ) {
            a[i] = *ws - '0';
            i++;
            ws++;
        } else {
            ws++;
        }
    }
    
    bcm2835_gpio_write(PIN1, a[0]);
    bcm2835_gpio_write(PIN2, a[1]);
    bcm2835_gpio_write(PIN3, a[2]);
    bcm2835_gpio_write(PIN4, a[3]);
    bcm2835_delay(50);
}
