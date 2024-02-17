// File providing functions for operating the motors, to be used in more complex movement/ junction related functions
// Also contains the function for flashing the blue LED, as this is dependent on the motor speeds being non-zero

#include "motor.h"
#include "utils.h"

// Currently unused global motor speed multipliers
#define multiplier_leftspeed 1
#define multiplier_rightspeed 1

// Set up motorshield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Assign motors to ports 1 and 4
Adafruit_DCMotor* leftmotor = AFMS.getMotor(1);
Adafruit_DCMotor* rightmotor = AFMS.getMotor(4);

// Variables for remembering last speeds
int last_leftspeed = 0;
int last_rightspeed = 0;

// Variable to flag if the robot is moving - if so blue LED must flash
bool is_moving = false;

// Assign blue LED pin 7
int blue_led = 7;

// Initialising motors and checking they exist - if not print an error message
void MOT_initialise() {
    pinMode(blue_led, OUTPUT);

    if (!AFMS.begin()) {
        UTIL_error("Could not find left Motor Shield. Check wiring.\n");
    }
    if (!AFMS.begin()) {
        UTIL_error("Could not find left Motor Shield. Check wiring.\n");
    }
    UTIL_log(LOG_INFO, "Both Motor Shields found.\n");

    // This is needed for the motors to work I think, stolen from the Electronics Getting Started document
    leftmotor->run(RELEASE);
    rightmotor->run(RELEASE);
}

/*
Function to set motor speeds only if they need to change
Use MOT_setspeeds(0,0) to stop
Variable is_moving is false if speeds are 0,0, otherwise it is true
*/
void MOT_setspeeds(int leftspeed, int rightspeed) {
    if (leftspeed == 0 and rightspeed == 0) {
        is_moving = false;
    }
    else {
        is_moving = true;
    }
    // Only set new motor speeds if the new speed is different to the current speed
    if ((last_leftspeed != leftspeed) or (last_rightspeed != rightspeed)) {
        // UTIL_log(LOG_DEBUG, "Setting motors: %d, %d\n", leftspeed, rightspeed); ***** Useful line for debugging motors
        if (leftspeed < 0) {
            leftmotor->run(FORWARD);
        }
        else {
            leftmotor->run(BACKWARD);
        }
        if (rightspeed < 0) {
            rightmotor->run(FORWARD);
        }
        else {
            rightmotor->run(BACKWARD);
        }
	    leftmotor->setSpeed(abs(leftspeed) * multiplier_leftspeed);
	    rightmotor->setSpeed(abs(rightspeed) * multiplier_rightspeed);
        last_leftspeed = leftspeed;
        last_rightspeed = rightspeed;
    }
}

// Function to flash blue LED if is_moving is true, to be used with a ticker in the main loop
void LED_flashblue() {
    if (is_moving == false) {
        digitalWrite(blue_led, LOW);
    }
    else {
        // Toggle blue LED
        digitalWrite(blue_led, !digitalRead (blue_led));
    }
}