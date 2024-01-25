#include "src/motor.h"
#include "src/line_sensor.h"
#include "src/line_follow_straight_basic.h"
#include "Ticker.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
  // put your setup code here, to run once:
  bluetimer.start();
  MOT_initialise();
  LS_setup();
}
void loop() {
  // put your main code here, to run repeatedly:
  bluetimer.update();
  MOT_setspeeds(200,200);
}
