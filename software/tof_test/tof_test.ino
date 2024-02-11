#include "src/line_sensor.h"
#include "src/flipper.h"
#include "src/motor.h"
#include "src/utils.h"

#define SERVO_CLOSED_ANGLE 135 /*add fully closed angle here*/
#define SERVO_OPEN_ANGLE 63 /*add fully open angle here*/
#define SERVO_COMPACT_ANGLE 100 /*default angle for stowing the flipper*/

void setup() {
  Serial.begin(115200);
  SENSE_setup_tof();
  MOT_initialise();
  SERV_initialise();
  SERV_turn_to_angle(SERVO_OPEN_ANGLE);
}

void loop() {
    int reading = SENSE_read_tof();
    UTIL_log(LOG_INFO, "Read: %i\n", reading);
    delay(50);
}
