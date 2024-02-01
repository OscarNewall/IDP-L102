#include "navigation.h"
#include "state_machine.h"
#include "line_follow_straight_basic.h"
#include "junction.h"

NAV_turns_e state;

void state_machine() {
// Function to run repeatedly in main loop, executing the list of states in turns_order from navigation.cpp
    if (state == NAV_LINE_FOLLOW) {
        if (!straight_basic(255,127)) {
            state = NAV_next();
            JUNC_enter();
            Serial.println("Exiting line following");
        }
    }

    else if (state == NAV_JUNC_LEFT) {
        if (!JUNC_turn_loop(true)) { // True for left
            state = NAV_next();
            Serial.println("Exiting left turn");
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }

    else if (state == NAV_JUNC_RIGHT) {
        if (!JUNC_turn_loop(false)) { // False for right
            state = NAV_next();
            Serial.println("Exiting right turn");
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }

    else if (state == NAV_BLIND_FORWARDS) {
        if (!blind_forwards()) {
            state = NAV_next();
            Serial.println("Exiting blind forwards");
            JUNC_enter();
        }
    }

    else if (state == NAV_JUNC_PASS) {
        if (!JUNC_pass_loop()) {
            state = NAV_next();
            Serial.println("Exiting junction pass");
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
    
}