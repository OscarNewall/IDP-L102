#include "junction_id.h"

#include <stdint.h>

#include "line_sensor.h"
#include "motor.h"

#define FORWARD_SPEED 200
#define FORWARD_TIME_MS 700
#define TURN_SPEED 100

static uint32_t turn_start_time;

void JUNC_enter() {
    turn_start_time = millis();
}

bool JUNC_pass_loop() {
    if (millis() - turn_start_time < FORWARD_TIME_MS) {
        MOT_setspeeds(FORWARD_SPEED, FORWARD_SPEED);
        return true;
    }

    MOT_setspeeds(0, 0);
    return false;
}

bool JUNC_turn_loop(bool is_left) {
    LS_data_t ls_out = LS_read();

    if (millis() - turn_start_time < FORWARD_TIME_MS) {
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