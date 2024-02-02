#include "flipper.h"
#include "utils.h"
#include <Servo.h>

Servo myservo;
int previous_servo_pos = 0;
int servo_pos = 0;
int servo_pin;// NEED TO INPUT SERVO PIN NUMBER HERE

void SERV_initialise() {
// Function to be added to ino setup loop
    myservo.attach(servo_pin);
}

void SERV_turn_to_angle(int target_pos) {
// Function to turn the servo from its last position to a new target position, whether that is forwards or backwards
    if (previous_servo_pos == target_pos) {
        return;
    }
    else if (previous_servo_pos < target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos <= target_pos; servo_pos += 1) {
            myservo.write(servo_pos);
            // Need to add delay here
        }
    }
    else if (previous_servo_pos > target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos >= target_pos; servo_pos -= 1) {
            myservo.write(servo_pos);
            // Need to add delay here
        }
    }
    previous_servo_pos = target_pos;
}
