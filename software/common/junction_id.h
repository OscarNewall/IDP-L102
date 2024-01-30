#ifndef JUNCTION_ID_H
#define JUNCTION_ID_H

typedef enum {
    JUNC_END,
    JUNC_LEFT,
    JUNC_RIGHT,
    JUNC_T,
} JUNC_types_e;

void JUNC_left_turn_enter();

bool JUNC_left_turn_loop();

#endif