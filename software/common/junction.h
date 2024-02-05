#ifndef JUNCTION_H
#define JUNCTION_H

typedef enum {
    JUNC_END,
    JUNC_LEFT,
    JUNC_RIGHT,
    JUNC_T,
} JUNC_types_e;

bool JUNC_pass_loop();

bool JUNC_turn_loop(bool is_left);

#endif