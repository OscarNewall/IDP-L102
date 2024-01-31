#include "src/line_follow_straight_basic.h"
#include "src/junction_id.h"
#include "src/navigation.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    bluetimer.start();
    state = NAV_next();
}

void loop() {

    bluetimer.update(); // Run the movement LED for #safety :)

    if (state == NAV_LINE_FOLLOW) {
        if (!straight_basic(255,127)) {
            state = NAV_next();
            JUNC_ENTER();
      }
    }
    else if (state == NAV_JUNC_LEFT) {
        if (!JUNC_turn_loop(bool is_left = true)) { // True for left
            state = NAV_next();
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
    else if (state == NAV_JUNC_RIGHT) {
        if (!JUNC_turn_loop(bool is_left = false)) { // False for right
            state = NAV_next();
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
    else if (state == BLIND_FORWARDS) {
        if (!blind_forwards()) {
            state = NAV_next();
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
    else if (state == JUNC_PASS) {
        if (!JUNC_pass_loop()) {
            state = NAV_next();
            // Don't need to JUNC_ENTER here as next state always NAV_LINE_FOLLOW
        }
    }
}
