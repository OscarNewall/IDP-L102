#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

static NAV_turns_e state;

void STATE_setup() {
    state = NAV_next();
    JUNC_enter();
    UTIL_log(LOG_INFO, "Initial state: %s", states[state]);
}

void STATE_loop() {
// Function to run repeatedly in main loop, executing the list of states in turns_order from navigation.cpp
    if (state == NAV_LINE_FOLLOW) {
        if (!MOVE_line_follow_loop()) {
            state = NAV_next();
            JUNC_enter();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_LEFT) {
        if (!JUNC_turn_loop(true)) { // True for left
            state = NAV_next();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }

    else if (state == NAV_JUNC_RIGHT) {
        if (!JUNC_turn_loop(false)) { // False for right
            state = NAV_next();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }

    else if (state == NAV_BLIND_FORWARDS) {
        if (!MOVE_blind_forward_loop()) {
            state = NAV_next();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
            JUNC_enter();
        }
    }

    else if (state == NAV_JUNC_PASS) {
        if (!JUNC_pass_loop()) {
            state = NAV_next();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
    
}