// Test file for printing line sensor outputs

#include "src/line_sensor.h"
#include "src/motor.h"

void setup() {
  Serial.begin(9600);
  LS_setup();
  MOT_initialise();
}

void loop() {
  LS_data_t line_sensor_data = LS_read();

  Serial.print("Far left: ");
  Serial.print(line_sensor_data.far_left);
  Serial.print(" Left: ");
  Serial.print(line_sensor_data.left);
  Serial.print(" Right: ");
  Serial.print(line_sensor_data.right);
  Serial.print(" Far right: ");
  Serial.println(line_sensor_data.far_right);

  delay(500);
}
