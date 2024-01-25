#include "junction_id.h"

#include "line_sensor.h"
#include "motor.h"

#define SEARCH_SPEED 100

typedef enum {
    FAR_LEFT_TRIGGERED,
    FAR_RIGHT_TRIGGERED,
} JUNC_state_e;

static JUNC_state_e state;

JUNC_types_e JUNC_identify() {
    LS_data_t ls_out = LS_read();

    if (ls_out.far_left and ls_out.far_right) {
        return JUNC_T;
    }
    else if (ls_out.far_left) {
        state = FAR_LEFT_TRIGGERED;
    }
    else if (ls_out.far_right) {
        state = FAR_RIGHT_TRIGGERED;
    }

    while (true) {
        ls_out = LS_read();

        if (state == FAR_LEFT_TRIGGERED) {
            if (!ls_out.far_left) {
                return JUNC_LEFT;
            }
            else if (ls_out.far_right) {
                return JUNC_T;
            }

            MOT_setspeeds(SEARCH_SPEED, SEARCH_SPEED);
        }

        else if (state == FAR_RIGHT_TRIGGERED) {
            if (!ls_out.far_right) {
                return JUNC_RIGHT;
            }
            else if (ls_out.far_left) {
                return JUNC_T;
            }

            MOT_setspeeds(SEARCH_SPEED, SEARCH_SPEED);
        }
    }
}