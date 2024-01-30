#include "junction_id.h"

#include "line_sensor.h"
#include "motor.h"

#define SEARCH_SPEED 100

#define TURN_INNER_SPEED -50
#define TURN_OUTER_SPEED 100

static bool far_left_triggered;
static bool far_right_triggered;

JUNC_types_e JUNC_identify() {
    far_left_triggered = false;
    far_right_triggered = false;

    MOT_setspeeds(SEARCH_SPEED, SEARCH_SPEED);
    
    while (true) {
        LS_data_t ls_out = LS_read();


        far_left_triggered |= ls_out.far_left;
        far_right_triggered |= ls_out.far_right;

        if (far_left_triggered and far_right_triggered) {
            return JUNC_T;
        }

        if (far_left_triggered and !ls_out.far_left) {
            return JUNC_LEFT;
        }

        if (far_right_triggered and !ls_out.far_right) {
            return JUNC_RIGHT;
        }
    }
}

bool JUNC_left_turn() {
    LS_data_t ls_out = LS_read();

    if (!ls_out.far_left && ls_out.left && ls_out.right && !ls_out.far_right) {
        MOT_setspeeds(0, 0);
        return false;
    }

    MOT_setspeeds(TURN_INNER_SPEED, TURN_OUTER_SPEED);

    return true;
}