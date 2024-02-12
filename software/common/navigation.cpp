#include "navigation.h"

#include "utils.h"

char *states[] = {
    "NAV_END",
    "NAV_JUNC_FORWARD_LEFT",
    "NAV_JUNC_FORWARD_RIGHT",
    "NAV_JUNC_REVERSE_LEFT",
    "NAV_JUNC_REVERSE_RIGHT",
    "NAV_JUNC_PASS",
    "NAV_JUNC_CONFIRM",
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
// Currently unused
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

static NAV_turns_e route_res2_to_green_to_finish[] = {
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
    NAV_INIT_180_LEFT,
    NAV_COMPLETE_180_LEFT,
    NAV_STOW_FLIPPER,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_JUNC_PASS, // second JUNC_PASS used to move further into box
    NAV_END,
};

static NAV_turns_e route_res2_to_red_to_finish[] = {
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
    NAV_INIT_180_RIGHT,
    NAV_COMPLETE_180_RIGHT,
    NAV_STOW_FLIPPER,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_JUNC_PASS, // second JUNC_PASS used to move further into box
    NAV_END
};

static bool delivered_res1_block = false;
static bool delivered_res2_block = false;
static const NAV_turns_e* current_turn_pos = route_start_to_res1;

void NAV_setup_custom_path(const NAV_turns_e* state_array_start) {
    delivered_res1_block = true;
    delivered_res2_block = true;
    current_turn_pos = state_array_start;
}

NAV_turns_e NAV_initial_state() {
    return *current_turn_pos;
}

NAV_turns_e NAV_next_state(STATE_result_e result) {
    switch (result) {
        case STATE_EXIT:
            current_turn_pos++;
            break;
        case STATE_DETECTION_FOAM:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                current_turn_pos = route_res1_to_green_to_res2;
            }
            else if (!delivered_res2_block) {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_green_to_finish;
            }
            else { 
                // Avoid changing route on custom path
                current_turn_pos++;
            }
            break;
        case STATE_DETECTION_SOLID:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                current_turn_pos = route_res1_to_red_to_res2;
            }
            else if (!delivered_res2_block) {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_red_to_finish;
            }
            else {
                // Avoid changing route on custom path
                current_turn_pos++;
            }
            break;
        default:
            UTIL_error("Unexpected result passed to NAV_next: %i", result);
    }

    return *current_turn_pos;
}