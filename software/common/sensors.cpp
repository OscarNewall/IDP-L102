// File containing functions relating to all inputs other than start button and limit switch

#include "sensors.h"
#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_VL53L0X.h>
#include "utils.h"

// Declare a LS_data_t type struct (defined in header) to store previous LS input
static LS_data_t prev_data;

// Assign the line sensor pins as inputs
void LS_setup() {
    pinMode(left_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
    pinMode(right_line_pin, INPUT);
    pinMode(far_left_line_pin, INPUT);
}

// Function returning true if the LS input has not changed since the last readings
static bool data_unchanged(LS_data_t new_data) {
    return (
        prev_data.far_left == new_data.far_left &&
        prev_data.left == new_data.left &&
        prev_data.right == new_data.right &&
        prev_data.far_right == new_data.far_right
    );
}

// Function returning a LS_data_t type struct of the current LS readings
LS_data_t LS_read() {
    LS_data_t data;

    data.left = digitalRead(left_line_pin);
    data.far_left = digitalRead(far_left_line_pin);
    data.right = digitalRead(right_line_pin);
    data.far_right = digitalRead(far_right_line_pin);

    // If the readings have changed at all, log the change for help with debugging 
    if (!data_unchanged(data)) {
        UTIL_log(LOG_DEBUG, "LS: %u %u %u %u\n", data.far_left, data.left, data.right, data.far_right);
    }

    prev_data = data;
    return data;
}

/*
Following code creates an array of LS_data_t type structs and fills it with readings from the line sensors,
then returns a LS_data_t struct where for a sensor to be true or false at least half its values in the array
must be true or false respectively
*/
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

// Create the TOF sensor object
static DFRobot_VL53L0X tof_sensor;

// Function to setup the TOF sensor
void SENSE_setup_tof() {
    Wire.begin();
    tof_sensor.begin(0x50);
    tof_sensor.setMode(tof_sensor.eContinuous, tof_sensor.eLow);
    tof_sensor.start();
}

// Function to return the distance reading from the TOF sensor as an integer
int SENSE_read_tof() {
    float distance_reading = tof_sensor.getDistance();
    return static_cast<int>(distance_reading);
}