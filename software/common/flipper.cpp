#include "flipper.h"
#include "state_machine.h"
#include <Arduino.h>

Servo myservo;
int previous_servo_pos = 0;
int servo_pos = 0;
int servo_pin;// NEED TO INPUT SERVO PIN NUMBER HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool switch_pressed = false;
int crashswitchPin;// NEED TO INPUT SWITCH PIN NUMBER HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void SERV_initialise() {
// Function to be added to ino setup loop, initialises servo and block detection switch
    myservo.attach(servo_pin);
    pinMode(crashswitchPin, INPUT);
}

void SERV_turn_to_angle(int target_pos) {
// Function to turn the servo from its last position to a new target position, whether that is forwards or backwards
// Will block anything else from running while the servo is turning
    if (previous_servo_pos == target_pos) {
        return;
    }
    else if (previous_servo_pos < target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos <= target_pos; servo_pos += 1) {
            myservo.write(servo_pos);
            int val = digitalRead(crashswitchPin); // read input from crashswitch
            if (val == LOW) {
                // switch pressed if LOW
                switch_pressed = true;
            }
            delay(15);
        }
    }
    else if (previous_servo_pos > target_pos) {
        for (servo_pos = previous_servo_pos; servo_pos >= target_pos; servo_pos -= 1) {
            myservo.write(servo_pos);
            int val = digitalRead(crashswitchPin); // read input from crashswitch
            if (val == LOW) {
                // switch pressed if LOW
                switch_pressed = true;
            }
            delay(15);
        }
    }
    previous_servo_pos = target_pos;
}

bool SERV_drop_off() {
// State function to drop off block
    SERV_turn_to_angle(/*add fully open angle here*/);
    return false;
}

bool SERV_pick_up_and_detect() {
// Moves servo from fully open to fully closed, if limit switch is pressed then returns hard if not returns soft
    SERV_turn_to_angle(/*Fully closed*/);
    if (switch_pressed == false) {
        return DETECTION_FOAM;
    }
    else {
        // Reset switch_pressed for next time, then return that block was solid
        switch_pressed == false;
        return DETECTION_SOLID;
    }
}
