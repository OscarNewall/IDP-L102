// File to test the flipper and help set the correct angles for the Servo

#include "src/flipper_and_detection.h"
#include "src/state_machine.h"

int startbuttonPin = 3;

void setup() {
    Serial.begin(9600);
    SERV_initialise();
    pinMode(green_led, OUTPUT);
    pinMode(red_led, OUTPUT);
    pinMode(startbuttonPin, INPUT);
    
    while (1){
        int val = digitalRead(startbuttonPin);
        if (val == HIGH){
            break;
        }
    }
}

void loop() {
    SERV_turn_to_angle(67); // go to OPEN
    delay(2000);
    SERV_pick_up_and_detect(); // go to CLOSED (pickup action here)
    delay(2000);
    SERV_turn_to_angle(67); // go to OPEN
    delay(2000);
    SERV_turn_to_angle(100); // COMPACT
    while (1) {
      delay(1000);
    }
}