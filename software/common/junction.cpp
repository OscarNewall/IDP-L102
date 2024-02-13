#include "junction.h"

#include <stdint.h>

#include "line_sensor.h"
#include "motor.h"
#include "line_follow_straight_basic.h"
#include "utils.h"

#define FORWARD_TIME_MS 225
#define SHORT_FORWARD_TIME_MS 175 // For turns where the junction has been reversed into, so shorter step forward needed
#define TURN_SPEED 200
#define PARTIAL_TURN_TIME_MS 800  // Time for a ~60 degree turn
#define CONFIRM_TURN_NUDGE_MS 100

STATE_result_e JUNC_pass_loop() {
    if (!UTIL_reached_timeout(FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return STATE_REPEAT;
    }

    MOT_setspeeds(0, 0);
    return STATE_EXIT;
}

STATE_result_e JUNC_turn_loop(bool is_left, bool short_forward_step) {
    /*
    Should drive forward blindly for forward_time,
    then turn blindly for PARTIAL_TURN_TIME_MS,
    then continue turning until only both middle line sensors are on
    */
    LS_data_t ls_out = LS_read();

    unsigned long forward_time = short_forward_step ? SHORT_FORWARD_TIME_MS : FORWARD_TIME_MS;
    // if (!is_left && short_forward_step) {
    //     forward_time = (forward_time* 12) / 2;
    // }
    if (STATE_is_new_state()) {
        UTIL_log(LOG_DEBUG, "JUNC forward time: %lums\n", forward_time);
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
    LS_data_t ls_out = LS_read();

    // Blind reversing a little
    if (!UTIL_reached_timeout(FORWARD_TIME_MS*3)) {
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
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return STATE_REPEAT;
}

STATE_result_e JUNC_complete_180_loop(bool is_left) {
    LS_data_t ls_out = LS_read();

    if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return STATE_REPEAT;
}

STATE_result_e JUNC_confirm_turn_loop() {
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
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
        return STATE_REPEAT;
    }
    else if (ls_out.right) {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
        return STATE_REPEAT;
    }
}
