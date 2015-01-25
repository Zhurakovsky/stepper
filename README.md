stepper
=======
useful debounsing description: 
http://stackoverflow.com/questions/16306901/c-program-a-button-to-perform-a-task-once-when-pressed-latch


how to control stepper motor from raspberry pi and bcm2835

so, there are effective sequense of instructions for stepper motor:
8-steps
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
    
4-steps:
    while ( counter > 0 ) {
        bcm2835_gpio_write(PIN1, HIGH);
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
        bcm2835_gpio_write(PIN3, HIGH);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);

        bcm2835_gpio_write(PIN1, HIGH);
        bcm2835_gpio_write(PIN2, LOW);
        bcm2835_gpio_write(PIN3, HIGH);
        bcm2835_gpio_write(PIN4, LOW);
        bcm2835_delay(50);

        counter -= 1;
    }
