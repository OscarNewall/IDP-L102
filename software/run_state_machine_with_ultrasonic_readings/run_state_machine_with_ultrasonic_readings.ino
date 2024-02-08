#include "src/line_follow_straight_basic.h"
#include "src/junction.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"
#include "src/flipper.h"

//skjdfguia

#include "Arduino.h"
#include "Wire.h"

#define sensorPin A0

float ultrasonic_distance;
int samples = 5;
int temp_total = 0;

//skalgfu;a

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    SERV_initialise();
    bluetimer.start();

    int startbuttonPin = 3; // can change
    pinMode(startbuttonPin, INPUT);
    
    while (1){
        int val = digitalRead(startbuttonPin);
        if (val == HIGH){
            break;
        }

    }

    STATE_setup();

}

void loop() {

    bluetimer.update(); // Run the movement LED for #safety :)
    STATE_loop(); // Enact the list of states

    //khsdgfYILGW
    temp_total = 0;
    // Get ultrasonic reading averaged over a few samples
    for (int i = 0; i < samples; i++) {
        int raw_distance = analogRead(sensorPin);
        temp_total += raw_distance;
    }
    float ultrasonic_distance = temp_total/samples;

    Serial.println(ultrasonic_distance);
    delay(20);
    //Sjdfhg
    /*
    Use below code for seeing line sensor output
    LS_data_t data = LS_read();
    UTIL_log("%u %u %u %u \n",data.far_left,data.left,data.right,data.far_right);
    */
}
