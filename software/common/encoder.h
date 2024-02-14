#ifndef encoder_h
#define encoder_h

#include <Arduino.h>
#include <Ticker.h>
#include "motor.h"

void left_callback();
void right_callback();
void equal_forward(int);
void equal_backward(int);
void equal_left(int);
void equal_right(int);

#endif