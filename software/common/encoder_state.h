#ifndef encoder_state_h
#define encoder_state_h

#include <Arduino.h>
#include <Ticker.h>
#include "motor.h"

void left_callback();
void right_callback();
void encoder_initialise();
bool encoder_reached_count(unsigned int);
void encoder_forward();
void encoder_backward();
void encoder_left();
void encoder_right();
#endif