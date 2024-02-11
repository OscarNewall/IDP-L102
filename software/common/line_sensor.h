// header guard
#ifndef line_sensor_h
#define line_sensor_h

#include <Arduino.h>

// pin definitions
#define far_left_line_pin 13
#define left_line_pin 12

#define right_line_pin 11
#define far_right_line_pin 10

typedef struct {
    bool left;
    bool far_left;
    bool right;
    bool far_right;
} LS_data_t;

void LS_setup();

LS_data_t LS_read();

// Makes new reading and stores in buffer
void LS_new_read();

// Averages readings in buffer and returns result
LS_data_t LS_get_data();

void SENSE_setup_tof();

int SENSE_read_tof();

void SENSE_setup_ultrasonic();

float SENSE_read_ultrasonic();

#endif