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
    
     /*
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
    */
