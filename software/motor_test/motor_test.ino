// Tests the motors and blue LED

#include "src/motor.h"
#include "src/line_sensor.h"
#include "src/line_follow_straight_basic.h"
#include "src/utils.h"
#include "Ticker.h"

Ticker bluetimer(LED_flashblue, 500, 0, MILLIS);

void setup() {
  Serial.begin(9600);
  LS_setup();
  MOT_initialise();
  bluetimer.start();

  int startbuttonPin = 3;
  pinMode(startbuttonPin, INPUT);
    
  while (1){
      // Robot stuck in this loop until start button pressed
      int val = digitalRead(startbuttonPin);
      if (val == HIGH){
          break;
      }

  }

  STATE_setup();

}
void loop() {
  // Update blue LED ticker and set motors to full speed
  bluetimer.update();
  MOT_setspeeds(255,255);
}
