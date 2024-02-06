#include "src/flipper.h"

void setup() {
    Serial.begin(9600);
    SERV_initialise();
}

void loop() {
// goes to 10, waits 3s, goes to 90, waits 3s, goes to 140, waits 3s, goes back to 10, waits a minute.
    SERV_turn_to_angle(10);
    delay(3000);
    SERV_turn_to_angle(90);
    delay(3000);
    SERV_turn_to_angle(140);
    delay(3000);
    SERV_turn_to_angle(10);
    delay(60000);
}