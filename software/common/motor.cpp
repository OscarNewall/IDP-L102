#include "motor.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor* leftmotor = AFMS.getMotor(1);
Adafruit_DCMotor* rightmotor = AFMS.getMotor(2);

int last_leftspeed = 0;
int last_rightspeed = 0;

bool is_moving = false;

// Initialising motors and checking they exist
void MOT_initialise() {
    if (!AFMS.begin()) {
        Serial.println("Could not find left Motor Shield. Check wiring.");
        while (1);
    }
    if (!AFMS.begin()) {
        Serial.println("Could not find right Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Both Motor Shields found.");
}

// Function to set motor speeds only if they need to change
// Use MOT_setspeeds(0,0) to stop
// is_moving false if speeds are 0,0
// Otherwise true
void MOT_setspeeds(int leftspeed, int rightspeed) {
    if (leftspeed == 0 and rightspeed ==0) {
        is_moving = false;
    }
    else {
        is_moving = true;
    }
    if ((last_leftspeed != leftspeed) or (last_rightspeed != rightspeed)) {
        if (leftspeed < 0) {
            leftmotor->run(BACKWARD);
        }
        else {
            leftmotor->run(FORWARD);
        }
        if (rightspeed < 0) {
            rightmotor->run(BACKWARD);
        }
        else {
            rightmotor->run(FORWARD);
        }
	    leftmotor->setSpeed(abs(leftspeed));
	    rightmotor->setSpeed(abs(rightspeed));
        last_leftspeed = leftspeed;
        last_rightspeed = rightspeed;
    }
}