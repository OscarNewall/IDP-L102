#include "junction.h"

#include <stdint.h>

#include "line_sensor.h"
#include "motor.h"
#include "line_follow_straight_basic.h"
#include "utils.h"

#define FORWARD_TIME_MS 350
#define SHORT_FORWARD_TIME_MS 250 // For turns where the junction has been reversed into, so shorter step forward needed
#define TURN_SPEED 200
#define PARTIAL_TURN_TIME_MS 300  // Time for a ~60 degree turn

bool JUNC_pass_loop() {
    if (!UTIL_reached_timeout(FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }

    MOT_setspeeds(0, 0);
    return false;
}

bool JUNC_turn_loop(bool is_left, bool short_forward_step) {
    /*
    Should drive forward blindly for forward_time,
    then turn blindly for PARTIAL_TURN_TIME_MS,
    then continue turning until only both middle line sensors are on
    */
    LS_data_t ls_out = LS_read();

    const unsigned long forward_time = short_forward_step ? SHORT_FORWARD_TIME_MS : FORWARD_TIME_MS;

    if (!UTIL_reached_timeout(forward_time)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }

    if (UTIL_reached_timeout(forward_time + PARTIAL_TURN_TIME_MS)) {
        if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
            MOT_setspeeds(0, 0);
            return false;
        }
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return true;
}

bool JUNC_init_180_loop(bool is_left) {
    LS_data_t ls_out = LS_read();

    // Blind reversing a little
    if (!UTIL_reached_timeout(FORWARD_TIME_MS*2)) {
            MOT_setspeeds(-FORWARD_SPEED, -FORWARD_SPEED);
            return true;
        }

    // Break if both middle sensors off line
    if (!ls_out.left && !ls_out.right) {
        MOT_setspeeds(0, 0);
        return false;
    }

    // If not continue to turn left/right
    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return true;
}

