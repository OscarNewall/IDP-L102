#include "line_sensor.h"

#include "utils.h"

void LS_setup() {
    pinMode(left_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
    pinMode(right_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
}

LS_data_t LS_read() {
    LS_data_t data;

    data.left = digitalRead(left_line_pin);
    data.far_left = digitalRead(far_left_line_pin);
    data.right = digitalRead(right_line_pin);
    data.far_right = digitalRead(far_right_line_pin);

    UTIL_log(LOG_DEBUG, "LS: %u %u %u %u\n", data.far_left, data.left, data.right, data.far_right);

    return data;
}