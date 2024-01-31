#ifndef line_follow_straight_basic_h
#define line_follow_straight_basic_h

#include <Arduino.h>
#include "motor.h"
#include "line_sensor.h"

#define FORWARD_SPEED 255
#define LF_CORRECTION_SPEED 127

bool straight_basic(int, int);

bool blind_forwards();

#endif