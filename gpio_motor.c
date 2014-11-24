// compile: sudo gcc gpiotest.c -o gpiotest.exe -l bcm2835
#include <bcm2835.h>
#include <stdio.h>

#define PIN1 RPI_V2_GPIO_P1_12
#define PIN2 RPI_V2_GPIO_P1_16
#define PIN3 RPI_V2_GPIO_P1_18
#define PIN4 RPI_V2_GPIO_P1_22

int main() {
    if ( !bcm2835_init() ) {
        return 1;
    }
    int counter =  -1;
    printf("Input number of steps: ");
    scanf("%d", &counter);
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
    while ( counter > 0 ) {
        bcm2835_gpio_write(PIN1, HIGH);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, LOW);
        bcm2835_gpio_write(PIN4, HIGH);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, LOW);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, LOW);
        bcm2835_gpio_write(PIN4, HIGH);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, LOW);
        bcm2835_gpio_write(PIN2, HIGH);
        bcm2835_gpio_write(PIN3, LOW);
        bcm2835_gpio_write(PIN4, HIGH);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, LOW);
        bcm2835_gpio_write(PIN2, HIGH);
        bcm2835_gpio_write(PIN3, LOW);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, LOW);
        bcm2835_gpio_write(PIN2, HIGH);
        bcm2835_gpio_write(PIN3, HIGH);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, LOW);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, HIGH);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, HIGH);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, HIGH);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);
        bcm2835_gpio_write(PIN1, HIGH);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, LOW);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);
        counter -= 1;
    }
    bcm2835_gpio_write(PIN1, LOW);
    bcm2835_gpio_write(PIN2, LOW);
    bcm2835_gpio_write(PIN3, LOW);
    bcm2835_gpio_write(PIN4, LOW);
    bcm2835_close();
    return 0;
}

