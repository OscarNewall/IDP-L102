#include "line_follow_straight_basic.h"

void straight_basic(int speed_high, int speed_low) {
    LS_data_t data = LS_read();
    if (data.far_left == 1 or data.far_right == 1 or data.left == 0 and data.right == 0)
    {
        MOT_setspeeds(0, 0);
    }
    else if (data.left == 1 and data.right == 1)
    {
        MOT_setspeeds(speed_high, speed_high);
    }
    else if (data.left == 1 and data.right == 0)
    {
        MOT_setspeeds(speed_low, speed_high);
    }
    else if (data.left == 0 and data.right == 1)
    {
        MOT_setspeeds(speed_high, speed_low);
    }  
}