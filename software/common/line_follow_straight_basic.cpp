#include "line_follow_straight_basic.h"

bool MOVE_line_follow_loop() {
    LS_data_t data = LS_read();
    if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0))
    {
        MOT_setspeeds(0, 0);
        return false;
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
    return true;
}

bool MOVE_blind_forward_loop() {
    LS_data_t data = LS_read();

    if (data.far_left == 1 || data.left == 1 || data.right == 1 || data.far_right == 1) {
        MOT_setspeeds(0, 0);
        return false;
    }

    MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    return true;
}

bool MOVE_reverse_line_follow_loop() {
    LS_data_t data = LS_read();
    if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0))
    {
        MOT_setspeeds(0, 0);
        return false;
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
    return true;
}