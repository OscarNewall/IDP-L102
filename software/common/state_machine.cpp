#include "flipper.h"
#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

static NAV_turns_e state;

STATE_result_e STATE_sleep_loop(unsigned long time_ms) {
    MOT_setspeeds(0, 0);
    return UTIL_reached_timeout(time_ms) ? STATE_EXIT : STATE_REPEAT;
}

void STATE_setup() {
    state = NAV_next();
    UTIL_reset_start_time();
    UTIL_log(LOG_INFO, "Initial state: %s\n", states[state]);
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
}

void STATE_loop() {
// Function to run repeatedly in main loop, executing the list of states in turns_order from navigation.cpp
    STATE_result_e result;

    if (state == NAV_END) {
        // Only log message once
        if (result != STATE_REPEAT) {
            MOT_setspeeds(0, 0);
            UTIL_log(LOG_WARNING, "Reached %s, stopping\n", states[state]);
            result = STATE_REPEAT;
        }
    }
    else if (state == NAV_LINE_FOLLOW) {
        result = MOVE_line_follow_loop();
    }
    else if (state == NAV_REVERSE_LINE_FOLLOW) {
        result = MOVE_reverse_line_follow_loop();
    }
    else if (state == NAV_JUNC_FORWARD_LEFT) {
        result = JUNC_turn_loop(true, false);
    }
    else if (state == NAV_JUNC_FORWARD_RIGHT) {
        result = JUNC_turn_loop(false, false);
    }
    else if (state == NAV_JUNC_REVERSE_LEFT) {
        result = JUNC_turn_loop(true, true);
    }
    else if (state == NAV_JUNC_REVERSE_RIGHT) {
        result = JUNC_turn_loop(false, true);
    }
    else if (state == NAV_BLIND_FORWARDS) {
        result = MOVE_blind_forward_loop();
    }
    else if (state == NAV_JUNC_PASS) {
        result = JUNC_pass_loop();
    }
    else if (state == NAV_SLEEP) {
        result = STATE_sleep_loop(1000);
    }
    else if (state == NAV_INIT_180_LEFT) {
        result = JUNC_init_180_loop(true);
    }
    else if (state == NAV_INIT_180_RIGHT) {
        result = JUNC_init_180_loop(false);
    }
    else if (state == NAV_LINE_FOLLOW_FOR_TIME) {
        result = MOVE_line_follow_for_time(1500);
    }
    else if (state == NAV_BLOCK_PICKUP) {
        result = SERV_pick_up_and_detect();
    }
    else if (state == NAV_BLOCK_DROPOFF) {
        result = SERV_drop_off();
    }
    else if (state == NAV_STOW_FLIPPER) {
        result = SERV_stow_flipper();
    }
    else if (state == NAV_LINE_FOLLOW_TO_BLOCK) {
        result = MOVE_line_follow_to_block_loop();
    }
    else if (state == NAV_INDICATE_SOLID) {
        digitalWrite(red_led, HIGH); // While in this state make sure red led is on and vehicle is stationary
        result = STATE_sleep_loop(5500);
    }
    else if (state == NAV_INDICATE_FOAM) {
        digitalWrite(green_led, HIGH); // While in this state make sure green led is on and vehicle is stationary
        result = STATE_sleep_loop(5500);
    }
    else if (state == NAV_COMPLETE_180_LEFT) {
        result = JUNC_complete_180_loop(true);
    }
    else if (state == NAV_COMPLETE_180_RIGHT) {
        result = JUNC_complete_180_loop(false);
    }

    if (result != STATE_REPEAT) {
        digitalWrite(red_led, LOW);
        digitalWrite(green_led, LOW);
        state = NAV_next(result);
        UTIL_reset_start_time();
        UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
    }
