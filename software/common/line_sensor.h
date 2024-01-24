// header guard
#ifndef line_sensor_h
#define line_sensor_h

#include <Arduino.h>

// pin definitions
#define left_line_pin 2
#define far_left_line_pin 0

#define right_line_pin 0
#define far_right_line_pin 0

typedef struct {
    bool left;
    bool far_left;
    bool right;
    bool far_right;
} LS_data_t;

void LS_setup();

LS_data_t LS_read();

#endif