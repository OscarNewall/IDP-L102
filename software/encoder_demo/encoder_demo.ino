#include "src/encoder.h"

#define left_encoder_pin 14
#define right_encoder_pin 15

void setup() {
    Serial.begin(9600);
    MOT_initialise();
    pinMode(left_encoder_pin, INPUT_PULLUP);
    pinMode(right_encoder_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(left_encoder_pin), left_callback, RISING);
    attachInterrupt(digitalPinToInterrupt(right_encoder_pin), right_callback, RISING);
}

void loop() {
    equal_forward(6);
    equal_right(6);
}