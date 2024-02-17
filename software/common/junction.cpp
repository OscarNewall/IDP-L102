// File containing functions for navigating junctions and turning the robot

#include "junction.h"
#include <stdint.h>
#include "line_sensor.h"
#include "motor.h"
#include "line_follow_straight_basic.h"
#include "utils.h"

// Defining some movement related numbers that are likely to need tweaking
#define FORWARD_TIME_MS 225
#define SHORT_FORWARD_TIME_MS 205 // For turns where the junction has been reversed into, so shorter step forward needed
#define TURN_SPEED 200
#define PARTIAL_TURN_TIME_MS 950  // Time for a ~60 degree turn (very roughly)
#define CONFIRM_TURN_NUDGE_MS 100

STATE_result_e JUNC_pass_loop() {
// Function to blindly go forwards for a short time, in order to pass a junction
    if (!UTIL_reached_timeout(FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return STATE_REPEAT;
    }

    MOT_setspeeds(0, 0);
    return STATE_EXIT;
}

STATE_result_e JUNC_turn_loop(bool is_left, bool short_forward_step) {
    /*
    Drive forward blindly for forward_time,
    then turn blindly for PARTIAL_TURN_TIME_MS,
    then continue turning until both middle line sensors are back on
    */
    LS_data_t ls_out = LS_read(); // Grab data from line sensors

    unsigned long forward_time = short_forward_step ? SHORT_FORWARD_TIME_MS : FORWARD_TIME_MS;

    if (STATE_is_new_state()) {
        UTIL_log(LOG_DEBUG, "JUNC forward time: %lums\n", forward_time); // Print chosen forward_time to help with debugging
    }

    if (!UTIL_reached_timeout(forward_time)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return STATE_REPEAT;
    }

    if (UTIL_reached_timeout(forward_time + PARTIAL_TURN_TIME_MS)) {
        // For left turn require X110 in line sensor readings
        // For right turn require 011X in line sensor readings
        bool far_outside_off =  (is_left ? !ls_out.far_right : !ls_out.far_left);
        if (ls_out.left && ls_out.right && far_outside_off) {
            MOT_setspeeds(0, 0);
            return STATE_EXIT;
        }
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return STATE_REPEAT;
}

STATE_result_e JUNC_init_180_loop(bool is_left) {
/* Function to initialise a 180 degree turn from an outpost (after reversing a little so that
the flipper does not push the just delivered block off the platform) by turning on the spot 
until middle sensors off the line */
    LS_data_t ls_out = LS_read();

    // Blind reversing a little
    if (!UTIL_reached_timeout(FORWARD_TIME_MS*2.5)) {
            MOT_setspeeds(-FORWARD_SPEED, -FORWARD_SPEED);
            return STATE_REPEAT;
        }

    // Break if both middle sensors off line
    if (!ls_out.left && !ls_out.right) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    // If not continue to turn left/right
    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        // Left motor is faster so need to reduce left motor speed for it to turn on the spot accurately
        MOT_setspeeds(TURN_SPEED*0.9, -TURN_SPEED); 
    }

    return STATE_REPEAT;
}

STATE_result_e JUNC_complete_180_loop(bool is_left) {
// Function to finish a 180 manouver by turning until both middle sensors are back on the line
    LS_data_t ls_out = LS_read();

    if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) { // If 0110, exit
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED*0.9, -TURN_SPEED); // Left motor needs factor of 0.9 to turn without drifting too much
    }

    return STATE_REPEAT;
}

STATE_result_e JUNC_confirm_turn_loop() {
// Function to drive forwards a small amount and then straighten up onto the line if a middle sensor comes off
// Useful to add coming out of problematic junctions 
    if (!UTIL_reached_timeout(CONFIRM_TURN_NUDGE_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return STATE_REPEAT;
    }

    LS_data_t ls_out = LS_read();

    if (ls_out.left && ls_out.right) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }
    else if (ls_out.left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED*1.1);
        return STATE_REPEAT;
    }
    else if (ls_out.right) {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED*1.1);
        return STATE_REPEAT;
    }
}

STATE_result_e JUNC_turn_90(bool is_left) {
/* 
Function to blindly turn for a set time, then drive forwards a little to get far sensors off line,
then reverse and turn backwards until both far sensors are just back on the line, producing a good 90 degree turn
Useful for turning off the line into an industrial zone
*/
    LS_data_t ls_out = LS_read();

    if (!UTIL_reached_timeout(800)) {
        if (is_left) {
            MOT_setspeeds(-FORWARD_SPEED, FORWARD_SPEED);
        }
        else {
            MOT_setspeeds(FORWARD_SPEED, -FORWARD_SPEED);  
        }
        return STATE_REPEAT;
    }

    if (UTIL_reached_timeout(800 + 500)) {
        // Go forward a bit after the blind turn
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    }

    if (ls_out.far_left && ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }
    else if (!ls_out.far_left && ls_out.far_right) {
        MOT_setspeeds(-FORWARD_SPEED, 0);
    }
    else if (ls_out.far_left && !ls_out.far_right) {
        MOT_setspeeds(0, -FORWARD_SPEED);
    }
    else {
        MOT_setspeeds(-FORWARD_SPEED, -FORWARD_SPEED);
    }
    return STATE_REPEAT;
}