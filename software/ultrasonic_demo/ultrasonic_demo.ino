//Any libraries to be included go here
//Any global variables go in here
// Any function prototypes go here
#include "Arduino.h"
#include "Wire.h"


#define sensorPin A0

float ultrasonic_distance;
int samples = 5;
int temp_total = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){

    temp_total = 0;
    // Get ultrasonic reading averaged over a few samples
    for (int i = 0; i < samples; i++) {
        int raw_distance = analogRead(sensorPin);
        temp_total += raw_distance;
    }
    float ultrasonic_distance = temp_total/samples;

    Serial.println(ultrasonic_distance);
    delay(500);

}


