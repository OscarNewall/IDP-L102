#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum {
    REPEAT,
    EXIT,
    ERROR,
    DETECTION_SOLID,
    DETECTION_FOAM,
} STATE_result_e;

void STATE_setup();

void STATE_loop();

#endif