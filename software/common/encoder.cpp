#include "encoder.h"

#define step 1
#define interval 20

int left_count;
int right_count;
unsigned long left_timestamp;
unsigned long right_timestamp;
int offset;
int left_direction = 1;
int right_direction = 1;

void left_callback() {
    unsigned long new_timestamp = millis();
    if ((new_timestamp - left_timestamp) < 40) {
        left_count++;
        left_timestamp = new_timestamp;
    }
}

void right_callback() {
    unsigned long new_timestamp = millis();
    if ((new_timestamp - right_timestamp) < 40) {
        right_count++;
        right_timestamp = new_timestamp;
    }
}

void correct_speed() {
    int difference = left_count - right_count;
    int left_speed = 255;
    int right_speed = 255;

    if (difference > 0) {
        offset += difference;
    }
    else if (difference < 0) {
        offset -= difference;
    }

    if (offset > 0) {
        left_speed -= offset * step;
    }
    else if (offset < 0) {
        right_speed +- offset * step;
    }

    MOT_setspeeds(left_speed * left_direction, right_speed * right_direction);
}

void equal_drive(int count, int left_direction_arg = 1, int right_direction_arg = 1) {
    offset = 0;
    left_count = 0;
    right_count = 0;
    Ticker tickerObject(correct_speed, interval, 0, MILLIS);
    tickerObject.start();
    while (left_count < count || right_count < count) {
        tickerObject.update();
    }
}

void equal_forward(int count) {
    equal_drive(count, 1, 1);
}

void equal_backward(int count) {
    equal_drive(count, -1, -1);
}

void equal_left(int count) {
    equal_drive(count, -1, 1);
}

void equal_right(int count) {
    equal_drive(count, 1, -1);
}