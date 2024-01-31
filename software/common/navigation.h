#ifndef NAVIGATION_H
#define NAVIGATION_H

typedef enum {
    NAV_LEFT,
    NAV_RIGHT,
    NAV_STRAIGHT,
    NAV_BLIND,
} NAV_turns_e;

NAV_turns_e NAV_next();

/*
Current design questions:
    - options for navigation
        - left, right, straight, pickup block, reverse
    - junction type
        - do we need to know shape of junction for left turn etc
*/

#endif