#include "line_sensor.h"

#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_VL53L0X.h>

#include "utils.h"

#define ULTRASONIC_PIN_NO A0
#define ULTRASONIC_READINGS_COUNT 5
#define ULTRASONIC_MAX_RANG (520) // the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ULTRASONIC_ADC_SOLUTION (1023) //ADC accuracy of Arduino UNO is 10bit


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

#define BUF_SIZE 10

static LS_data_t data_buffer[BUF_SIZE];

static unsigned int buf_index = 0;

void LS_new_read() {
    data_buffer[buf_index] = LS_read();
    buf_index++;
    buf_index = buf_index % BUF_SIZE;
}

LS_data_t LS_get_data() {
    unsigned int far_left, left, right, far_right = 0;
    for (unsigned int i = 0; i < BUF_SIZE; i++) {
        far_left += data_buffer[i].far_left;
        left += data_buffer[i].left;
        right += data_buffer[i].right;
        far_right += data_buffer[i].far_right;
    }

    LS_data_t output;
    output.far_left = far_left > (BUF_SIZE / 2);
    output.left = left > (BUF_SIZE / 2);
    output.right = right > (BUF_SIZE / 2);
    output.far_right = far_right > (BUF_SIZE / 2);
    return output;
}

static DFRobot_VL53L0X tof_sensor;

void SENSE_setup_tof() {
    Wire.begin();
    tof_sensor.begin(0x50);
    tof_sensor.setMode(tof_sensor.eContinuous, tof_sensor.eLow);
    tof_sensor.start();
}

int SENSE_read_tof() {
    float distance_reading = tof_sensor.getDistance();
    return static_cast<int>(distance_reading);
}

int SENSE_read_ultrasonic() {
    int total = 0;

    for (int i = 0; i < ULTRASONIC_READINGS_COUNT; i++) {
        int raw_distance = analogRead(ULTRASONIC_PIN_NO);
        total += raw_distance;
    }
    return (total * ULTRASONIC_MAX_RANG) / (ULTRASONIC_ADC_SOLUTION * ULTRASONIC_READINGS_COUNT);
}
