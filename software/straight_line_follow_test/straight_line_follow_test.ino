#include "src/line_follow_straight_basic.h"
#include "src/motor.h"
#include "Ticker.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
  Serial.begin(9600);
  LS_setup();
  MOT_initialise();
  bluetimer.start();
}

void loop() {
  straight_basic(255, 150);
  bluetimer.update();
}