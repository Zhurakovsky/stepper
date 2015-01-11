// compile: sudo gcc gpiotest.c -o gpiotest.exe -l bcm2835
// version 0.1 master
#include <bcm2835.h>
#include <stdio.h>

#define PIN1 RPI_V2_GPIO_P1_12
#define PIN2 RPI_V2_GPIO_P1_16
#define PIN3 RPI_V2_GPIO_P1_18
#define PIN4 RPI_V2_GPIO_P1_22
#define PIN5 RPI_V2_GPIO_P1_07
#define PIN6 RPI_V2_GPIO_P1_11
#define PIN7 RPI_V2_GPIO_P1_15

void prepareStep(char *s[], int steps, int counter);
void makeStep(char *ws);

int main() {
    int scale = 0;
    int i;
    int counter =  -1;
    char* steps4[4];
    char* steps8[8];
    char* workingSteps;
    char *blankString = "0 0 0 0";
    
    if ( !bcm2835_init() ) {
        return 1;
    }
    
    steps4[0] = "1 0 0 1";
    steps4[1] = "0 1 0 1";
    steps4[2] = "0 1 1 0";
    steps4[3] = "1 0 1 0";
    
    steps8[0] = "1 0 0 1";
    steps8[1] = "0 0 0 1";
    steps8[2] = "0 1 0 1";
    steps8[3] = "0 1 0 0";
    steps8[4] = "0 1 1 0";
    steps8[5] = "0 0 1 0";
    steps8[6] = "1 0 1 0";
    steps8[7] = "1 0 0 0";
    
    printf("Input 4 or 8 steps per cycle '0' for exit: ");
    scanf("%d", &scale);
    while ( scale != 4 && scale != 8 ) {
        if ( scale == 0 ) {
            break;
        }
        printf("Input 4 or 8 steps per cycle '0' for exit: ");
        scanf("%d", &scale);
    }
    

    if ( scale != 0 ) {
        counter = 1;
    }
    
    if ( scale == 4 ) {
        prepareStep(steps4, scale, counter);
    } else if ( scale == 8 ) {
        prepareStep(steps8, scale, counter);
    } else {
        return 0;
    }
    
    makeStep(blankString);
    bcm2835_close();
    
    return 0;
}

void prepareStep(char *s[], int scale, int counter) {
    int a[4];
    int i;
    char *ws;
    char *blankString = "0 0 0 0";
    uint8_t valueOnSix, valueOnSeven;
    
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_write(PIN5, HIGH);
    bcm2835_gpio_write(PIN6, LOW);
    bcm2835_gpio_write(PIN7, LOW);
    
    while ( counter > 0 ) {
        valueOnSix = bcm2835_gpio_lev(PIN6);
        valueOnSeven = bcm2835_gpio_lev(PIN7);
        if ( valueOnSix == 1 ) {
            for ( i = 0; i < scale; i++ ) {
                ws = s[i];
                makeStep(ws);
            }

        } else if ( valueOnSeven == 1 ) {
            for ( i = scale - 1; i >= 0; i-- ) {
                ws = s[i];
                makeStep(ws);
            }

        }
        valueOnSix = 0;
        valueOnSeven = 0;
        makeStep(blankString);
    }
    makeStep(blankString);
}

void makeStep(char *ws) {
    int a[4];
    int i;
    
    for ( i = 0; i < 4 && *ws != '\0'; ) {
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
