#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

static NAV_turns_e state;

void STATE_setup() {
    state = NAV_next();
    UTIL_reset_start_time();
    UTIL_log(LOG_INFO, "Initial state: %s\n", states[state]);
}

void STATE_loop() {
// Function to run repeatedly in main loop, executing the list of states in turns_order from navigation.cpp
    if (state == NAV_LINE_FOLLOW) {
        if (!MOVE_line_follow_loop()) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    if (state == NAV_REVERSE_LINE_FOLLOW) {
        if (!MOVE_reverse_line_follow_loop()) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_FORWARD_LEFT) {
        if (!JUNC_forward_turn_loop(true)) { // True for left
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_FORWARD_RIGHT) {
        if (!JUNC_forward_turn_loop(false)) { // False for right
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_REVERSE_LEFT) {
        if (!JUNC_reverse_turn_loop(true)) { // True for left
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_REVERSE_RIGHT) {
        if (!JUNC_reverse_turn_loop(false)) { // False for right
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_BLIND_FORWARDS) {
        if (!MOVE_blind_forward_loop()) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_PASS) {
        if (!JUNC_pass_loop()) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_SLEEP) {
        if (!UTIL_sleep_loop()) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }
    
}