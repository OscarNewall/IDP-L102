#ifndef NAVIGATION_H
#define NAVIGATION_H

/*
Plan for 180 turns is to blind reverse a little,
then turn left/right until middle sensors off the line
(left for coming out of green, right for coming out of red, 
in order to avoid hitting wall),
then do a standard left/right turn back onto the line
(either regular or short forward step)

In navigation.cpp 180 will look like:
NAV_INIT_180_(LEFT/RIGHT)
NAV_JUNC_REVERSE_(LEFT/RIGHT)
*/

typedef enum {
    NAV_JUNC_FORWARD_LEFT,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_JUNC_PASS,
    NAV_BLIND_FORWARDS,
    NAV_LINE_FOLLOW,
    NAV_SLEEP,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_INIT_180_LEFT,
    NAV_INIT_180_RIGHT
} NAV_turns_e; // Keep upto date with states in navigation.cpp

extern char* states[];

NAV_turns_e NAV_next();

#endif