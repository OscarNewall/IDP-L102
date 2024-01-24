#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Adafruit_MotorShield.h>

void MOT_initialise();
void MOT_setspeeds(int, int);

#endif