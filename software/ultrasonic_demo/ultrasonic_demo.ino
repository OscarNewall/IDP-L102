//Any libraries to be included go here
//Any global variables go in here
// Any function prototypes go here
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"


#define sensorPin A0
DFRobot_VL53L0X TOFsensor;

float tot, total;

void tof_initialise();

void setup() {
  Serial.begin(9600);
  tof_initialise();
}

void loop(){


}
bool block_is_foam(int samples = 5, float threshold = 9){
  for (int i = 0; i < samples; i++) {
    //TOF
    float TOFd = TOFsensor.getDistance();
    float tot += TOFd;

    //ultra
    int rc = analogRead(sensorPin);
    float total += rc;
  }

  float avg = total/samples;
  float TOF_avg = tot/ samples;

  bool foam = false;
  if (TOF_avg - avg < threshold){
    bool foam = true; //block is foam
  }
  return foam;
}
void tof_initialise() {
  Wire.begin();
  TOFsensor.begin(0x50);
  TOFsensor.setMode(TOFsensor.eContinuous,TOFsensor.eHigh);
  TOFsensor.start();

}

