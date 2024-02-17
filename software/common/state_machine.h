#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

// Assign pins to green and red LEDs
#define green_led 6
#define red_led 5

// Define an enum to cover all the state exit conditions
typedef enum {
    STATE_REPEAT,
    STATE_EXIT,
    STATE_ERROR,
    STATE_DETECTION_SOLID,
    STATE_DETECTION_FOAM,
} STATE_result_e;

STATE_result_e STATE_sleep_loop();
bool STATE_is_new_state();
void STATE_setup();
void STATE_loop();

#endif