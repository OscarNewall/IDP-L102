// File conatining functions related to straight line movement

#include "line_movement.h"
#include "utils.h"

// Will not return STATE_EXIT if a junction is detected within this time after entering the line follow state
#define NO_JUNC_TIMEOUT_MS 500

STATE_result_e MOVE_line_follow_loop() {
// Function for line following, returns STATE_EXIT if either far sensor is triggered after NO_JUNC_TIMEOUT_MS
    LS_data_t data = LS_read();

    // Will only exit state after timeout
    if (UTIL_reached_timeout(NO_JUNC_TIMEOUT_MS)) {
        if (data.far_left == 1 || data.far_right == 1) {
            MOT_setspeeds(0, 0);
            return STATE_EXIT;
        }
    }
    if (data.far_left) {
        MOT_setspeeds(0, FORWARD_SPEED);
    }
    else if (data.far_right) {
        MOT_setspeeds(FORWARD_SPEED, 0);
    }
    else if (data.left == 1 && data.right == 0)
    {
        MOT_setspeeds(LF_CORRECTION_SPEED, FORWARD_SPEED);
    }
    else if (data.left == 0 && data.right == 1)
    {
        MOT_setspeeds(FORWARD_SPEED, LF_CORRECTION_SPEED);
    }
    else 
    {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
    return STATE_REPEAT;
}

STATE_result_e MOVE_blind_forward_loop(bool is_forward) {
// Function for moving forwards off the line. Useful in start box and industrial area
    LS_data_t data = LS_read();

    // If any sensor back on line, exit
    if (data.far_left == 1 || data.left == 1 || data.right == 1 || data.far_right == 1) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    if (is_forward) {
        MOT_setspeeds(FORWARD_SPEED*0.9, FORWARD_SPEED); // Correction factor for left motor to acheive a straighter line
    }
    else {
        MOT_setspeeds(-FORWARD_SPEED, -FORWARD_SPEED); // Option to reverse
    }
    return STATE_REPEAT;
}

STATE_result_e MOVE_reverse_line_follow_loop() {
// Function for line following in reverse. Not the most stable but good enough to back out of residential zones
    LS_data_t data = LS_read();
    // If 3 or more sensors are on, exit
    if (data.far_left + data.left + data.right + data.far_right > 2)
    {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }
    else if (data.left == 1 && data.right == 1)
    {
        MOT_setspeeds(-FORWARD_SPEED, -FORWARD_SPEED);
    }
    else if (data.left == 1 && data.right == 0)
    {
        MOT_setspeeds(-LF_CORRECTION_SPEED*1.5, -FORWARD_SPEED);
    }
    else if (data.left == 0 && data.right == 1)
    {
        MOT_setspeeds(-FORWARD_SPEED, -LF_CORRECTION_SPEED*1.5);
    }
    return STATE_REPEAT;
}

STATE_result_e MOVE_line_follow_for_time(int time_ms) {
// Line follow using the earlier function for a set time, then exit. Useful for entering industrial zone off the line
    if (UTIL_reached_timeout(time_ms)) {
        return STATE_EXIT;
    }

    return MOVE_line_follow_loop();
}

STATE_result_e MOVE_line_follow_to_block_loop() {
// Function to line follow until the TOF sensor gives a reading < PICKUP_DISTANCE
    LS_data_t data = LS_read();

    int distance = SENSE_read_tof();
    UTIL_log(LOG_DEBUG, "Distance measured: %dcm\n", distance); // Record TOF distances for debugging

    if (distance < PICKUP_DISTANCE) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    return MOVE_line_follow_loop();
}