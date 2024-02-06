#include "flipper.h"

#include <Arduino.h>

Servo myservo;
int previous_servo_pos = 0;
int servo_pos = 0;
int servo_pin;// NEED TO INPUT SERVO PIN NUMBER HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void SERV_initialise() {
// Function to be added to ino setup loop
    myservo.attach(servo_pin);
}

void SERV_turn_to_angle(int target_pos) {
// Function to turn the servo from its last position to a new target position, whether that is forwards or backwards
// Will block anything else from running while the servo is turning - don't think this is a problem atm
    if (previous_servo_pos == target_pos) {
        return;
    }
    else if (previous_servo_pos < target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos <= target_pos; servo_pos += 1) {
            myservo.write(servo_pos);
            delay(15);
        }
    }
    else if (previous_servo_pos > target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos >= target_pos; servo_pos -= 1) {
            myservo.write(servo_pos);
            delay(15);
        }
    }
    previous_servo_pos = target_pos;
}
