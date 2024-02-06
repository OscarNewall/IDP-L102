#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <Ticker.h>

void MOT_initialise();
void MOT_setspeeds(int, int);
void LED_flashblue();

#endif