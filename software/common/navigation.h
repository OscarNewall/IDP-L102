#ifndef NAVIGATION_H
#define NAVIGATION_H

typedef enum {
    NAV_JUNC_FORWARD_LEFT,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_JUNC_PASS,
    NAV_BLIND_FORWARDS,
    NAV_LINE_FOLLOW,
    NAV_SLEEP,
    NAV_REVERSE_LINE_FOLLOW
} NAV_turns_e; // Keep upto date with states in navigation.cpp

extern char* states[];

NAV_turns_e NAV_next();

#endif