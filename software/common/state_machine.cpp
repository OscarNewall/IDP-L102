// File primarily for the main state machine function and related functions

#include "flipper.h"
#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

// Variable for holding the current state
static NAV_turns_e state;

// Function for stopping the robot for time_ms
STATE_result_e STATE_sleep_loop(unsigned long time_ms) {
    MOT_setspeeds(0, 0);
    return UTIL_reached_timeout(time_ms) ? STATE_EXIT : STATE_REPEAT;
}

// Declaring variable before use
static bool is_new_state;

// Function returning a boolean, true only on the first loop of a new state
bool STATE_is_new_state() {
    return is_new_state;
}

// Should be placed in the setup loop of .ino files
// Fetches initial state, sets LED pins, and prints the initial state's name
void STATE_setup() {
    state = NAV_initial_state();
    UTIL_reset_start_time();
    is_new_state = true;
    UTIL_log(LOG_INFO, "Initial state: %s\n", states[state]);
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
}


// Should be placed in the main loop of .ino files
// Runs code based on the current state and exits the state when appropriate, using NAV_next_state to enter a new state
void STATE_loop() {
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
        result = MOVE_blind_forward_loop(true);
    }
    else if (state == NAV_BLIND_REVERSE) {
        result = MOVE_blind_forward_loop(false);
    }
    else if (state == NAV_JUNC_PASS) {
        result = JUNC_pass_loop();
    }
    else if (state == NAV_JUNC_CONFIRM) {
        result = JUNC_confirm_turn_loop();
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
        result = MOVE_line_follow_for_time(3000);
    }
    else if (state == NAV_LINE_FOLLOW_INTO_INDUSTRIAL) {
        result = MOVE_line_follow_for_time(2500);
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
        digitalWrite(red_led, HIGH);
        result = STATE_sleep_loop(5500);
    }
    else if (state == NAV_INDICATE_FOAM) {
        digitalWrite(green_led, HIGH);
        result = STATE_sleep_loop(5500);
    }
    else if (state == NAV_COMPLETE_180_LEFT) {
        result = JUNC_complete_180_loop(true);
    }
    else if (state == NAV_COMPLETE_180_RIGHT) {
        result = JUNC_complete_180_loop(false);
    }
    else if (state == NAV_TURN_90_LEFT) {
        result = JUNC_turn_90(true);
    }


    is_new_state = false; // Reached end of first loop so it is no longer a new state
    if (result != STATE_REPEAT) {
        digitalWrite(red_led, LOW); // Turn off green & red LEDs in case they were activated
        digitalWrite(green_led, LOW);
        state = NAV_next_state(result); // Pass exit condition to NAV_next_state to get new state
        is_new_state = true; // Reset as next loop is new state
        UTIL_reset_start_time(); // Reset state timer
        UTIL_log(LOG_INFO, "Changing to %s\n", states[state]); // Print serial output for easy debugging
    }
}
