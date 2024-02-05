#include "junction.h"

#include <stdint.h>

#include "line_sensor.h"
#include "motor.h"
#include "line_follow_straight_basic.h"
#include "utils.h"

#define FORWARD_TIME_MS 1000
#define SHORT_FORWARD_TIME_MS 500 // For turns where the junction has been reversed into, so shorter step forward needed
#define TURN_SPEED 100

bool JUNC_pass_loop() {
    if (UTIL_reached_timeout(FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }

    MOT_setspeeds(0, 0);
    return false;
}

bool JUNC_forward_turn_loop(bool is_left) {
    LS_data_t ls_out = LS_read();

    if (UTIL_reached_timeout(FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }
    else if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return false;
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return true;
}

bool JUNC_reverse_turn_loop(bool is_left) {
    LS_data_t ls_out = LS_read();

    if (UTIL_reached_timeout(SHORT_FORWARD_TIME_MS)) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }
    else if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return false;
    }

    if (is_left) {
        MOT_setspeeds(-TURN_SPEED, TURN_SPEED);
    }
    else {
        MOT_setspeeds(TURN_SPEED, -TURN_SPEED);
    }

    return true;
}