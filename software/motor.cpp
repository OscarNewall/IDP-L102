#include "motor_h"

// Initialising motors and checking they exist
void MOT_initialise() {
    Adafruit_MotorShield AFMSleft = Adafruit_MotorShield(/*I2C address leftmotor*/);
    Adafruit_MotorShield AFMSright = Adafruit_MotorShield(/*I2C address rightmotor*/);

    Adafruit_DCMotor* leftmotor = AFMSleft.getMotor(/*left motor port number*/);
    Adafruit_DCMotor* rightmotor = AFMSright.getMotor(/*right motor port number*/);

    if (!AFMSleft.begin()) {
        Serial.println("Could not find left Motor Shield. Check wiring.");
        while (1);
    }
    if (!AFMSright.begin()) {
        Serial.println("Could not find right Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Both Motor Shields found.");
}

// Function to set motor speeds
// Use MOT_setspeeds(0,0) to stop
void MOT_setspeeds(int leftspeed, int rightspeed) {
    if (leftspeed < 0) {
        leftmotor->run(BACKWARD);
    }
    else {
        leftmotor->run(FORWARD)
    }
    if (rightspeed < 0) {
        rightmotor->run(BACKWARD);
    }
    else {
        rightmotor->run(FORWARD)
    }
	leftmotor->setSpeed(abs(leftspeed));
	rightmotor->setSpeed(abs(rightspeed));
}