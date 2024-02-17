// Header guard
#ifndef line_sensor_h
#define line_sensor_h

#include <Arduino.h>

// Pin definitions
#define far_left_line_pin 13
#define left_line_pin 12
#define right_line_pin 11
#define far_right_line_pin 10

// Define the LS_data_t structure for storing boolean LS values
typedef struct {
    bool left;
    bool far_left;
    bool right;
    bool far_right;
} LS_data_t;

// Declare functions
void LS_setup();
LS_data_t LS_read();
void LS_new_read();
LS_data_t LS_get_data();
void SENSE_setup_tof();
int SENSE_read_tof();

#endif