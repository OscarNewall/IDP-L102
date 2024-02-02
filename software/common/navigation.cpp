#include "navigation.h"

#include "utils.h"

char *states[] = {
    "NAV_JUNC_LEFT",
    "NAV_JUNC_RIGHT",
    "NAV_JUNC_PASS",
    "NAV_BLIND_FORWARDS",
    "NAV_LINE_FOLLOW",
    "NAV_SLEEP"
};

static const NAV_turns_e turns_order[] = {
    // For start box to nearest residential 
    /*NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_RIGHT,
    NAV_LINE_FOLLOW, */
    // At block
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
};

static unsigned int nav_pos_index = 0;

NAV_turns_e NAV_next() {
    // Stay in SLEEP if reached end of turns_order
    if (nav_pos_index >= ARRAY_SIZE(turns_order)) {
        UTIL_log(LOG_WARNING, "Reached end of states - at index %u\n", nav_pos_index);
        return NAV_SLEEP;
    }
    return turns_order[nav_pos_index++];
}