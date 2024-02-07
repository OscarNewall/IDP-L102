#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#define green_led 6
#define red_led 5

typedef enum {
    STATE_REPEAT,
    STATE_EXIT,
    STATE_ERROR,
    STATE_DETECTION_SOLID,
    STATE_DETECTION_FOAM,
} STATE_result_e;

STATE_result_e STATE_sleep_loop();

void STATE_setup();

void STATE_loop();

#endif