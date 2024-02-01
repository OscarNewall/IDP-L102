#ifndef line_follow_straight_basic_h
#define line_follow_straight_basic_h

#include <Arduino.h>
#include "motor.h"
#include "line_sensor.h"

#define FORWARD_SPEED 255
#define LF_CORRECTION_SPEED 127

bool MOVE_line_follow_loop();

bool MOVE_blind_forward_loop();

#endif