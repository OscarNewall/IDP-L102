#ifndef line_movement_h
#define line_movement_h

#include <Arduino.h>
#include "motor.h"
#include "sensors.h"
#include "state_machine.h"

#define FORWARD_SPEED 255
#define LF_CORRECTION_SPEED 127
#define PICKUP_DISTANCE 161
#define sensorPin A0

STATE_result_e MOVE_line_follow_loop();
STATE_result_e MOVE_blind_forward_loop(bool is_forward);
STATE_result_e MOVE_reverse_line_follow_loop();
STATE_result_e MOVE_line_follow_for_time(int time_ms);
STATE_result_e MOVE_line_follow_to_block_loop();

#endif