#include "navigation.h"

static const NAV_turns_e turns_order[] = {
    NAV_LEFT,
    NAV_STRAIGHT,
    NAV_LEFT,
    NAV_STRAIGHT,
    NAV_STRAIGHT,
    NAV_LEFT,
    NAV_LEFT,
};

static unsigned int nav_pos_index = 0;

NAV_turns_e NAV_next() {
    nav_pos_index++;
    nav_pos_index = nav_pos_index % (sizeof(turns_order) / sizeof(turns_order[0]));
    return turns_order[nav_pos_index];
}