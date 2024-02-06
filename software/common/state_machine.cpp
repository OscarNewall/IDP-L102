#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

static NAV_turns_e state;

int green_led = 6;
int red_led = 5;

void STATE_setup() {
    state = NAV_next();
    UTIL_reset_start_time();
    UTIL_log(LOG_INFO, "Initial state: %s\n", states[state]);
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
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
        if (!JUNC_turn_loop(true, false)) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_FORWARD_RIGHT) {
        if (!JUNC_turn_loop(false, false)) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_REVERSE_LEFT) {
        if (!JUNC_turn_loop(true, true)) { 
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_JUNC_REVERSE_RIGHT) {
        if (!JUNC_turn_loop(false, true)) {
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

    else if (state == NAV_INIT_180_LEFT) {
        if (!JUNC_init_180_loop(true)) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_INIT_180_RIGHT) {
        if (!JUNC_init_180_loop(false)) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_LINE_FOLLOW_FOR_TIME) {
        if (!MOVE_line_follow_for_time(2500)) {
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }
     
    else if (state == NAV_INDICATE_SOLID) {
        MOT_setspeeds(0, 0);
        digitalWrite(red_led, HIGH); // While in this state make sure red led is on and vehicle is stationary
        if (UTIL_reached_timeout(5500)) {
            digitalWrite(red_led, LOW); // Timer up so turn off red indicator led
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }

    else if (state == NAV_INDICATE_FOAM) {
        MOT_setspeeds(0, 0);
        digitalWrite(green_led, HIGH); // While in this state make sure green led is on and vehicle is stationary
        if (UTIL_reached_timeout(5500)) {
            digitalWrite(green_led, LOW); // Timer up so turn off green indicator led
            state = NAV_next();
            UTIL_reset_start_time();
            UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
        }
    }
}