#include "src/line_sensor.h"

void setup() {
  Serial.begin(9600);
  LS_setup();
}

void loop() {
  LS_data_t line_sensor_data = LS_read();
  Serial.println(line_sensor_data.left);
}
