// The main .ino file, as was used in the second competition

#include "src/line_movement.h"
#include "src/junction.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"
#include "src/flipper_and_detection.h"

// Initialise the blue LED's ticker and set the flashing to 2Hz
Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    // All necessary setup code goes here
    Serial.begin(115200);
    LS_setup();
    SENSE_setup_tof();
    MOT_initialise();
    SERV_initialise();
    bluetimer.start();

    int startbuttonPin = 3;
    pinMode(startbuttonPin, INPUT);
    while (1){
        // Robot is stuck in this loop until the start button is pressed
        int val = digitalRead(startbuttonPin);
        if (val == HIGH){
            break;
        }

    }

    // Involves starting the state timer so should be called after the robot is started
    STATE_setup();
}

// Main loop that runs continuously 
void loop() {
    bluetimer.update(); // Run the movement LED for #safety :)
    STATE_loop(); // Enact the list of states
}
