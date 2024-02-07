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
    "NAV_INDICATE_SOLID",
    "NAV_INDICATE_FOAM"
    "NAV_COMPLETE_180_LEFT",
    "NAV_COMPLETE_180_RIGHT"
};

static NAV_turns_e turns_order[] = {
// The array currently used by NAV_next()
    NAV_INIT_180_LEFT,
    NAV_COMPLETE_180_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    /*
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW_FOR_TIME
    */
};

static NAV_turns_e route_start_to_res1[] = {
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    // Need to add pickup and detection states here
};

static NAV_turns_e route_res1_to_green_to_res2[] = {
    NAV_INDICATE_FOAM,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW_FOR_TIME,
    // Need to add drop off state here
    NAV_INIT_180_LEFT,
    NAV_COMPLETE_180_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    // Need to add pickup and detection states here
};

static NAV_turns_e route_res1_to_red_to_res2[] = {
    NAV_INDICATE_SOLID,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW_FOR_TIME,
    // Need to add drop off state here
    NAV_INIT_180_RIGHT,
    NAV_COMPLETE_180_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    // Need to add pickup and detection states here
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
    NAV_LINE_FOLLOW_FOR_TIME,
    // Need to add drop off state here
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
    NAV_LINE_FOLLOW_FOR_TIME,
    // Need to add drop off state here
};

static bool delivered_res1_block = false;
static bool delivered_res2_block = false;
static NAV_turns_e* current_turn_pos = route_start_to_res1;

NAV_turns_e NAV_next(STATE_result_e result) {
    switch (result) {
        case STATE_EXIT:
            current_turn_pos++;
            break;
        case STATE_DETECTION_FOAM:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                current_turn_pos = route_res1_to_green_to_res2;
            }
            else {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_green;
            }
            break;
        case STATE_DETECTION_SOLID:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                current_turn_pos = route_res1_to_red_to_res2;
            }
            else {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_red;
            }
            break;
        default:
            UTIL_error("Unexpected result passed to NAV_next: %i", result);
    }

    return *current_turn_pos;
}