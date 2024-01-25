#include "src/line_follow_straight_basic.h"

void setup() {
  Serial.begin(9600);
  LS_setup();
  MOT_initialise();
}

void loop() {
  straight_basic(255, 220);
}