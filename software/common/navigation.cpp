#include "navigation.h"

#include "utils.h"

char *states[] = {
    "NAV_JUNC_FORWARD_LEFT",
    "NAV_JUNC_FORWARD_RIGHT",
    "NAV_JUNC_REVERSE_LEFT",
    "NAV_JUNC_REVERSE_RIGHT",
    "NAV_JUNC_PASS",
    "NAV_BLIND_FORWARDS",
    "NAV_LINE_FOLLOW",
    "NAV_SLEEP",
    "NAV_REVERSE_LINE_FOLLOW",
    "NAV_INIT_180_LEFT",
    "NAV_INIT_180_RIGHT",
    "NAV_LINE_FOLLOW_FOR_TIME",
    "NAV_BLOCK_PICKUP",
    "NAV_BLOCK_DROPOFF",
    "NAV_STOW_FLIPPER",
    "NAV_LINE_FOLLOW_TO_BLOCK",
    "NAV_INDICATE_SOLID",
    "NAV_INDICATE_FOAM",
    "NAV_COMPLETE_180_LEFT",
    "NAV_COMPLETE_180_RIGHT",
};

static NAV_turns_e turns_order[] = {
// The array currently used by NAV_next()
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

static NAV_turns_e route_start_to_res1[] = {
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

static NAV_turns_e route_res1_to_green_to_res2[] = {
    NAV_INDICATE_FOAM,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW_FOR_TIME, // use ultrasonic to end line follow?
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_LEFT,
    NAV_COMPLETE_180_LEFT,
    NAV_STOW_FLIPPER,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

static NAV_turns_e route_res1_to_red_to_res2[] = {
    NAV_INDICATE_SOLID,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW_FOR_TIME, // use ultrasonic to end line follow?
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_RIGHT,
    NAV_COMPLETE_180_RIGHT,
    NAV_STOW_FLIPPER,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

static NAV_turns_e route_res2_to_green[] = {
    NAV_INDICATE_FOAM,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME, // use ultrasonic to end line follow?
    NAV_BLOCK_DROPOFF,
};

static NAV_turns_e route_res2_to_red[] = {
    NAV_INDICATE_SOLID,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME, // use ultrasonic to end line follow?
    NAV_BLOCK_DROPOFF,
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