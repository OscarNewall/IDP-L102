#include "src/motor.h"
#include "src/line_sensor.h"
#include "src/line_follow_straight_basic.h"
#include "src/utils.h"
#include "Ticker.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetimer.start();
  MOT_initialise();
  LS_setup();
}
void loop() {
  // put your main code here, to run repeatedly:
  bluetimer.update();
  MOT_setspeeds(255,255);
  delay(500);
  MOT_setspeeds(-200,200);
  delay(500);
  MOT_setspeeds(200,-200);
  delay(500);
}
