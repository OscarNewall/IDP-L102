#ifndef line_follow_straight_basic_h
#define line_follow_straight_basic_h

#include <Arduino.h>
#include "motor.h"
#include "line_sensor.h"
#include "state_machine.h"

#define FORWARD_SPEED 255
#define LF_CORRECTION_SPEED 127


STATE_result_e MOVE_line_follow_loop();

STATE_result_e MOVE_blind_forward_loop();

STATE_result_e MOVE_reverse_line_follow_loop();

STATE_result_e MOVE_line_follow_for_time(int time_ms);

#endif