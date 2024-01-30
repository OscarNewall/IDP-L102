#include "junction_id.h"

#include "line_sensor.h"
#include "motor.h"

#define TURN_INNER_SPEED -50
#define TURN_OUTER_SPEED 100

bool JUNC_left_turn() {
    LS_data_t ls_out = LS_read();

    if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return false;
    }

    MOT_setspeeds(TURN_INNER_SPEED, TURN_OUTER_SPEED);

    return true;
}