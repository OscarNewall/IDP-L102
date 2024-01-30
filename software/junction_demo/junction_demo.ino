#include "src/line_follow_straight_basic.h"
#include "src/junction_id.h"

typedef enum {
    STRAIGHT,
    JUNC_TURN_LEFT,
} state_e;

state_e state;

void setup() {
    Serial.begin(9600);
    LS_setup();
    MOT_initialise();
    state = STRAIGHT;
}

void loop() {
    if (state == STRAIGHT) {
        if (!straight_basic(255, 220)) {
            state = JUNC_TURN_LEFT;
            Serial.println("Switching to JUNC_TURN_LEFT");
        }
    }
    else if (state == JUNC_TURN_LEFT) {
        if (!JUNC_left_turn()) {
            state = STRAIGHT;
            Serial.println("Switching to STRAIGHT");
        }
    }
}