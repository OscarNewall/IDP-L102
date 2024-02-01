#include "line_sensor.h"

#include "utils.h"

static LS_data_t prev_data;

void LS_setup() {
    pinMode(left_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
    pinMode(right_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
}

static bool data_unchanged(LS_data_t new_data) {
    return (
        prev_data.far_left == new_data.far_left &&
        prev_data.left == new_data.left &&
        prev_data.right == new_data.right &&
        prev_data.far_right == new_data.far_right
    );
}

LS_data_t LS_read() {
    LS_data_t data;

    data.left = digitalRead(left_line_pin);
    data.far_left = digitalRead(far_left_line_pin);
    data.right = digitalRead(right_line_pin);
    data.far_right = digitalRead(far_right_line_pin);

    if (!data_unchanged(data)) {
        UTIL_log(LOG_DEBUG, "LS: %u %u %u %u\n", data.far_left, data.left, data.right, data.far_right);
    }

    prev_data = data;
    return data;
}