#include "src/line_follow_straight_basic.h"
#include "src/junction.h"

typedef enum {
    STRAIGHT,
    JUNC_TURN_LEFT,
} state_e;

state_e state;

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    bluetimer.start();
    state = STRAIGHT;
}

void loop() {
    if (state == STRAIGHT) {
        if (!straight_basic(255, 127)) {
            state = JUNC_TURN_LEFT;
            JUNC_enter();
            Serial.println("Switching to JUNC_TURN_LEFT");
        }
    }
    else if (state == JUNC_TURN_LEFT) {
        if (!JUNC_turn_loop(true)) {
            state = STRAIGHT;
            Serial.println("Switching to STRAIGHT");
        }
    }
    bluetimer.update();
}