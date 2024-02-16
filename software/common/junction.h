#ifndef JUNCTION_H
#define JUNCTION_H

#include "state_machine.h"

typedef enum {
    JUNC_END,
    JUNC_LEFT,
    JUNC_RIGHT,
    JUNC_T,
} JUNC_types_e;

STATE_result_e JUNC_pass_loop();

STATE_result_e JUNC_turn_loop(bool is_left, bool short_forward_step);

STATE_result_e JUNC_init_180_loop(bool is_left);

STATE_result_e JUNC_complete_180_loop(bool is_left);

STATE_result_e JUNC_confirm_turn_loop();

STATE_result_e JUNC_turn_90(bool is_left);

#endif