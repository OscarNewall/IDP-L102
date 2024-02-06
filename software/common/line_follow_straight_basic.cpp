#include "line_follow_straight_basic.h"

#include "utils.h"

STATE_result_e MOVE_line_follow_loop() {
    LS_data_t data = LS_read();
    if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0))
    {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }
    else if (data.left == 1 && data.right == 1)
    {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
    else if (data.left == 1 && data.right == 0)
    {
        MOT_setspeeds(LF_CORRECTION_SPEED, FORWARD_SPEED);
    }
    else if (data.left == 0 && data.right == 1)
    {
        MOT_setspeeds(FORWARD_SPEED, LF_CORRECTION_SPEED);
    }
    return STATE_REPEAT;
}

STATE_result_e MOVE_blind_forward_loop() {
    LS_data_t data = LS_read();

    if (data.far_left == 1 || data.left == 1 || data.right == 1 || data.far_right == 1) {
        MOT_setspeeds(0, 0);
        return STATE_EXIT;
    }

    MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    return STATE_REPEAT;
}

STATE_result_e MOVE_reverse_line_follow_loop() {
    LS_data_t data = LS_read();
    if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0))
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
        MOT_setspeeds(-LF_CORRECTION_SPEED, -FORWARD_SPEED);
    }
    else if (data.left == 0 && data.right == 1)
    {
        MOT_setspeeds(-FORWARD_SPEED, -LF_CORRECTION_SPEED);
    }
    return STATE_REPEAT;
}

STATE_result_e MOVE_line_follow_for_time(int time_ms) {
    LS_data_t data = LS_read();
    
    if (!UTIL_reached_timeout(time_ms)) {
        if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0)) {
            MOT_setspeeds(0, 0);
            return STATE_EXIT;
        }
        else if (data.left == 1 && data.right == 1) {
            MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        }
        else if (data.left == 1 && data.right == 0) {
            MOT_setspeeds(LF_CORRECTION_SPEED, FORWARD_SPEED);
        }
        else if (data.left == 0 && data.right == 1) {
            MOT_setspeeds(FORWARD_SPEED, LF_CORRECTION_SPEED);
        }
        return STATE_REPEAT;
    }
    return STATE_EXIT;
}

