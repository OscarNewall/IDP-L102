#include "src/line_follow_straight_basic.h"
#include "src/junction.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"
#include "src/flipper.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    Serial.begin(9600);
    LS_setup();
    SENSE_setup_tof();
    MOT_initialise();
    SERV_initialise();
    bluetimer.start();

    int startbuttonPin = 3;
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
}
