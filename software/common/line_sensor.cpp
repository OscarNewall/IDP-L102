#include "line_sensor.h"

#include <Arduino.h>

static const int left_line_sensor_pin_no = 2;
static const int far_left_line_sensor_pin_no = 0;

static const int right_line_sensor_pin_no = 0;
static const int far_right_line_sensor_pin_no = 0;

void LS_setup() {
    pinMode(left_line_sensor_pin_no, INPUT);
    pinMode(far_left_line_sensor_pin_no, INPUT);
    pinMode(right_line_sensor_pin_no, INPUT);
    pinMode(far_right_line_sensor_pin_no, INPUT);
}

LS_data_t LS_read() {
    LS_data_t data;

    data.left = digitalRead(left_line_sensor_pin_no);
    data.far_left = digitalRead(far_left_line_sensor_pin_no);
    data.right = digitalRead(right_line_sensor_pin_no);
    data.far_right = digitalRead(far_right_line_sensor_pin_no);

    return data;
}