#include "src/line_follow_straight_basic.h"
#include "src/junction.h"
#include "src/navigation.h"
#include "src/state_machine.h"
#include "src/utils.h"
#include "src/flipper.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

const NAV_turns_e turns_order[] = {
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
    NAV_END
};

void setup() {
    Serial.begin(9600);
    NAV_setup_custom_path(turns_order);
    LS_setup();
    SENSE_setup_tof();
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
    // Serial.println(SENSE_read_tof());
    /*
    Use below code for seeing line sensor output
    LS_data_t data = LS_read();
    UTIL_log("%u %u %u %u \n",data.far_left,data.left,data.right,data.far_right);
    */
}
