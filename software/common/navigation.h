#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "state_machine.h"

// Define an enum to handle all the possible states the robot can be in
// Must keep up to date with the state names in navigation.cpp
typedef enum {
    NAV_END,
    NAV_JUNC_FORWARD_LEFT,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_JUNC_PASS,
    NAV_JUNC_CONFIRM,
    NAV_BLIND_FORWARDS,
    NAV_LINE_FOLLOW,
    NAV_SLEEP,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_INIT_180_LEFT,
    NAV_INIT_180_RIGHT,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_LINE_FOLLOW_INTO_INDUSTRIAL,
    NAV_BLOCK_PICKUP,
    NAV_BLOCK_DROPOFF,
    NAV_STOW_FLIPPER,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_INDICATE_SOLID,
    NAV_INDICATE_FOAM,
    NAV_COMPLETE_180_LEFT,
    NAV_COMPLETE_180_RIGHT,
    NAV_TURN_90_LEFT,
    NAV_BLIND_REVERSE
} NAV_turns_e;

extern char* states[];
void NAV_setup_custom_path(const NAV_turns_e* state_array_start);
NAV_turns_e NAV_initial_state();
NAV_turns_e NAV_next_state(STATE_result_e result);

#endif