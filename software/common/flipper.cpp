#include "flipper.h"

#include <Arduino.h>

#include "state_machine.h"
#include "utils.h"

#define SERVO_CLOSED_ANGLE 139 /*add fully closed angle here*/
#define SERVO_OPEN_ANGLE 60 /*add fully open angle here*/

Servo myservo;
int previous_servo_pos = 100;
int servo_pos = 0;
int servo_pin = 8;
bool switch_pressed = false;
int crashswitchPin = 2;

void SERV_initialise() {
// Function to be added to ino setup loop, initialises servo and block detection switch
    myservo.attach(servo_pin);
    pinMode(crashswitchPin, INPUT);
    SERV_turn_to_angle(100);
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
            delay(40);
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
            delay(40);
        }
    }
    previous_servo_pos = target_pos;
}

STATE_result_e SERV_drop_off() {
// State function to drop off block
    SERV_turn_to_angle(SERVO_OPEN_ANGLE);
    return STATE_EXIT;
}

// need to change func type here to fit returning enums
STATE_result_e SERV_pick_up_and_detect() {
// Moves servo from fully open to fully closed, if limit switch is pressed then returns hard if not returns soft
    SERV_turn_to_angle(SERVO_CLOSED_ANGLE);
    UTIL_log(LOG_INFO, "Switch pressed: %i\n", switch_pressed);
    if (switch_pressed == false) {
        return STATE_DETECTION_FOAM;
    }
    else {
        // Reset switch_pressed for next time, then return that block was solid
        switch_pressed == false;
        return STATE_DETECTION_SOLID;
    }
}