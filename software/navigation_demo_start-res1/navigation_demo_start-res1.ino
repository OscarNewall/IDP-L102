#include "src/line_follow_straight_basic.h"
#include "src/junction_id.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

// NAV_turns_e state;

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    bluetimer.start();
    state = NAV_next();
    Serial.print("Initial state: ");
    Serial.print(states[state]);
}

void loop() {

    bluetimer.update(); // Run the movement LED for #safety :)
    state_machine(); // Enact the list of states



    /*
    Use below code for seeing line sensor output
    LS_data_t data = LS_read();
    UTIL_log("%u %u %u %u \n",data.far_left,data.left,data.right,data.far_right);
    */
}
