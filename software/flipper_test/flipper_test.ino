#include "src/flipper.h"
#include "src/state_machine.h"

int startbuttonPin = 3;

void setup() {
    Serial.begin(9600);
    SERV_initialise(); // turns servo to 100 degrees or COMPACT
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
    STATE_result_e block_type = SERV_pick_up_and_detect(); // go to CLOSED (pickup action here) and light up correct led
    if (block_type == STATE_DETECTION_SOLID) { 
        digitalWrite(red_led, HIGH);
    }
    else {
        digitalWrite(green_led, HIGH);
    }
    delay(2000);
    SERV_turn_to_angle(67); // go to OPEN
    delay(2000);
    SERV_turn_to_angle(100); // COMPACT
    while (1) {
      delay(1000);
    }
}