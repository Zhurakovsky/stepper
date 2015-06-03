#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <fcntl.h> 

#define MOUSEFILE "/dev/input/event1"

void mouseListener();

int main() {
    
    pthread_t mouseThread, thread2;
    int mouseThreadError;
    
    return 0;
}

void mouseListener() {
    int fd;
    struct input_event ie;
    
    if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("opening device error");
        exit(EXIT_FAILURE);
    }
    while(read(fd, &ie, sizeof(struct input_event))) {
        while (ie.type != 274) {
            printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", 
                   ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
        }
        
    }
}

/*
 * The event structure itself
 
struct input_event {
    struct timeval time;
    __u16 type;
    __u16 code;
    __s32 value;
};

/*
 * Event types
 
#define EV_SYN 0x00 
#define EV_KEY 0x01 
#define EV_REL 0x02 
#define EV_ABS 0x03 
#define EV_MSC 0x04 
#define EV_SW 0x05 
#define EV_LED 0x11 
#define EV_SND 0x12 
#define EV_REP 0x14 
#define EV_FF 0x15 
#define EV_PWR 0x16 
#define EV_FF_STATUS 0x17 
#define EV_MAX 0x1f 
#define EV_CNT (EV_MAX+1) 
#define BTN_MOUSE 0x110 //272 
#define BTN_LEFT 0x110 //272 
#define BTN_RIGHT 0x111 //273 
#define BTN_MIDDLE 0x112 //274 
#define BTN_SIDE 0x113 
#define BTN_EXTRA 0x114 
#define BTN_FORWARD 0x115 
#define BTN_BACK 0x116 
#define BTN_TASK 0x117
*/
