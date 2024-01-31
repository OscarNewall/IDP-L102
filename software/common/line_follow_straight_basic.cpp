#include "line_follow_straight_basic.h"

bool straight_basic(int speed_high, int speed_low) {
    LS_data_t data = LS_read();
    if (data.far_left == 1 || data.far_right == 1 || (data.left == 0 && data.right == 0))
    {
        MOT_setspeeds(0, 0);
        return false;
    }
    else if (data.left == 1 && data.right == 1)
    {
        MOT_setspeeds(speed_high, speed_high);
    }
    else if (data.left == 1 && data.right == 0)
    {
        MOT_setspeeds(speed_low, speed_high);
    }
    else if (data.left == 0 && data.right == 1)
    {
        MOT_setspeeds(speed_high, speed_low);
    }
    return true;
}

bool blind_forwards() {
    LS_data_t data = LS_read();

    if (data.far_left == 1 || data.left == 1 || data.right == 1 || data.far_right == 1) {
        MOT_setspeeds(0, 0);
        return false;
    }

    MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
    return true;
}