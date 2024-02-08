#include "flipper.h"
#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"
#include "utils.h"

static NAV_turns_e state;

#define SLEEP_STATE_MS 1000

STATE_result_e STATE_sleep_loop() {
    MOT_setspeeds(0, 0);
    return UTIL_reached_timeout(SLEEP_STATE_MS) ? STATE_EXIT : STATE_REPEAT;
}

void STATE_setup() {
    state = NAV_next();
    UTIL_reset_start_time();
    UTIL_log(LOG_INFO, "Initial state: %s\n", states[state]);
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
}

static void next_state() {
    state = NAV_next();
    UTIL_reset_start_time();
    UTIL_log(LOG_INFO, "Changing to %s\n", states[state]);
}

void STATE_loop() {
// Function to run repeatedly in main loop, executing the list of states in turns_order from navigation.cpp
    if (state == NAV_LINE_FOLLOW) {
        if (MOVE_line_follow_loop() != STATE_REPEAT) {
            next_state();
        }
    }

    if (state == NAV_REVERSE_LINE_FOLLOW) {
        if (MOVE_reverse_line_follow_loop() != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_JUNC_FORWARD_LEFT) {
        if (JUNC_turn_loop(true, false) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_JUNC_FORWARD_RIGHT) {
        if (JUNC_turn_loop(false, false) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_JUNC_REVERSE_LEFT) {
        if (JUNC_turn_loop(true, true) != STATE_REPEAT) { 
            next_state();
        }
    }

    else if (state == NAV_JUNC_REVERSE_RIGHT) {
        if (JUNC_turn_loop(false, true) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_BLIND_FORWARDS) {
        if (MOVE_blind_forward_loop() != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_JUNC_PASS) {
        if (JUNC_pass_loop() != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_SLEEP) {
        if (STATE_sleep_loop() != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_INIT_180_LEFT) {
        if (JUNC_init_180_loop(true) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_INIT_180_RIGHT) {
        if (JUNC_init_180_loop(false) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_LINE_FOLLOW_FOR_TIME) {
        if (MOVE_line_follow_for_time(1500) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_BLOCK_PICKUP) {
        if (SERV_pick_up_and_detect() != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_BLOCK_DROPOFF) {
        if (SERV_drop_off() != STATE_REPEAT) {
            next_state();
        }
    }
     
    else if (state == NAV_INDICATE_SOLID) {
        MOT_setspeeds(0, 0);
        digitalWrite(red_led, HIGH); // While in this state make sure red led is on and vehicle is stationary
        if (UTIL_reached_timeout(5500)) {
            digitalWrite(red_led, LOW); // Timer up so turn off red indicator led
            next_state();
        }
    }

    else if (state == NAV_INDICATE_FOAM) {
        MOT_setspeeds(0, 0);
        digitalWrite(green_led, HIGH); // While in this state make sure green led is on and vehicle is stationary
        if (UTIL_reached_timeout(5500)) {
            digitalWrite(green_led, LOW); // Timer up so turn off green indicator led
            next_state();
        }
    }

    else if (state == NAV_COMPLETE_180_LEFT) {
        if (JUNC_complete_180_loop(true) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_COMPLETE_180_RIGHT) {
        if (JUNC_complete_180_loop(false) != STATE_REPEAT) {
            next_state();
        }
    }

    else if (state == NAV_LINE_FOLLOW_TO_BLOCK) {
        if (MOVE_line_follow_to_block_loop() != STATE_REPEAT) {
            next_state();
        }
    }
}