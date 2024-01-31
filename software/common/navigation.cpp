#include "navigation.h"

static const NAV_turns_e turns_order[] = {
    // For start box to nearest residential 
    NAV_BLIND_FORWARDS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_RIGHT,
    NAV_LINE_FOLLOW,
    // At block
};

static unsigned int nav_pos_index = 0;

NAV_turns_e NAV_next() {
    nav_pos_index++;
    nav_pos_index = nav_pos_index % (sizeof(turns_order) / sizeof(turns_order[0]));
    return turns_order[nav_pos_index];
}