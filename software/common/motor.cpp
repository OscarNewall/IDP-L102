#include "motor.h"

#include "utils.h"

#define multiplier_leftspeed 0.9
#define multiplier_rightspeed 1

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor* leftmotor = AFMS.getMotor(1);
Adafruit_DCMotor* rightmotor = AFMS.getMotor(4);

int last_leftspeed = 0;
int last_rightspeed = 0;

bool is_moving = false;
int blue_led = 7;

// Initialising motors and checking they exist
void MOT_initialise() {
    pinMode(blue_led, OUTPUT);

    if (!AFMS.begin()) {
        UTIL_error("Could not find left Motor Shield. Check wiring.\n");
    }
    if (!AFMS.begin()) {
        UTIL_error("Could not find left Motor Shield. Check wiring.\n");
    }
    UTIL_log(LOG_INFO, "Both Motor Shields found.\n");

    leftmotor->run(RELEASE);
    rightmotor->run(RELEASE);
}

// Function to set motor speeds only if they need to change
// Use MOT_setspeeds(0,0) to stop
// is_moving false if speeds are 0,0
// Otherwise true
void MOT_setspeeds(int leftspeed, int rightspeed) {
    if (leftspeed == 0 and rightspeed == 0) {
        is_moving = false;
    }
    else {
        is_moving = true;
    }
    if ((last_leftspeed != leftspeed) or (last_rightspeed != rightspeed)) {
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

// Blue movement LED flashing callback Function
void LED_flashblue() {
    if (is_moving == false) {
        digitalWrite(blue_led, LOW);
    }
    else {
        // If moving, toggle led
        digitalWrite(blue_led, !digitalRead (blue_led));
    }
}