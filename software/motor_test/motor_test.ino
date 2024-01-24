#include "src/motor.h"
#include "src//line_sensor.h"
#include "src//line_follow_straight_basic.h"

void setup() {
  // put your setup code here, to run once:
  MOT_initialise();
  LS_setup();
}
void loop() {
  // put your main code here, to run repeatedly:
  MOT_setspeeds(50,50)
  delay(2000)
  MOT_setspeeds(-25,25)
  delay(1000)
  MOT_setspeeds(50,50)
  delay(3000)
  while (1);
}
