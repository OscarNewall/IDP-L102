#include "src/line_follow_straight_basic.h"
#include "src/junction.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    STATE_setup();
    bluetimer.start();
}

void loop() {

    bluetimer.update(); // Run the movement LED for #safety :)
    STATE_loop(); // Enact the list of states

    /*
    Use below code for seeing line sensor output
    LS_data_t data = LS_read();
    UTIL_log("%u %u %u %u \n",data.far_left,data.left,data.right,data.far_right);
    */
}
