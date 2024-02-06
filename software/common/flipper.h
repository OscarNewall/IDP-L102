#ifndef flipper_h
#define flipper_h

#include "state_machine.h"

#include <Servo.h>

void SERV_initialise();
void SERV_turn_to_angle(int);
STATE_result_e SERV_pick_up_and_detect();

#endif