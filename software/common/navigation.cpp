/*
File for containing the routes (as arrays of states) between destinations, 
and also the function for deciding the next state (based on the arrays and variables recording which blocks have been delivered)
*/

#include "navigation.h"
#include "utils.h"

// Assign names to each state in the enum NAV_turns_e, for use in serial output and debugging
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
    "NAV_LINE_FOLLOW_FOR_TIME"
    "NAV_LINE_FOLLOW_INTO_INDUSTRIAL",
    "NAV_BLOCK_PICKUP",
    "NAV_BLOCK_DROPOFF",
    "NAV_STOW_FLIPPER",
    "NAV_LINE_FOLLOW_TO_BLOCK",
    "NAV_INDICATE_SOLID",
    "NAV_INDICATE_FOAM",
    "NAV_COMPLETE_180_LEFT",
    "NAV_COMPLETE_180_RIGHT",
    "NAV_TURN_90_LEFT",
    "NAV_BLIND_REVERSE"
};

// Currently unused array, was previously used during testing to set the route
static NAV_turns_e turns_order[] = {
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

// Array of the states needed to get from the start to the closest residential zone and pickup & detect the block
static NAV_turns_e route_start_to_res1[] = {
    NAV_BLIND_FORWARDS,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

/* 
Array of the states needed to get from the closest residential zone 
to deliver to green and then go to the far residential zone and pickup & detect the block */
static NAV_turns_e route_res1_to_green_to_res2[] = {
    NAV_INDICATE_FOAM,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_LEFT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP,
};

/* 
Array of the states needed to get from the closest residential zone 
to deliver to red and then to go to the far residential zone and pickup & detect the block */
static NAV_turns_e route_res1_to_red_to_res2[] = {
    NAV_INDICATE_SOLID,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_RIGHT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_RIGHT,
    NAV_JUNC_CONFIRM,
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

/* 
Array of the states needed to get from the far residential zone 
to deliver to green and then go to the leftmost industrial zone pickup & detect the block */
static NAV_turns_e route_res2_to_green_to_ind1[] = {
    NAV_INDICATE_FOAM,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_LEFT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW_INTO_INDUSTRIAL,
    NAV_JUNC_CONFIRM,
    NAV_JUNC_CONFIRM,
    NAV_TURN_90_LEFT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP

};

/* 
Array of the states needed to get from the far residential zone 
to deliver to red and then go to the leftmost industrial zone pickup & detect the block */
static NAV_turns_e route_res2_to_red_to_ind1[] = {
    NAV_INDICATE_SOLID,
    NAV_REVERSE_LINE_FOLLOW,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_RIGHT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW_INTO_INDUSTRIAL,
    NAV_JUNC_CONFIRM,
    NAV_JUNC_CONFIRM,
    NAV_TURN_90_LEFT,
    NAV_BLOCK_DROPOFF,
    NAV_LINE_FOLLOW_TO_BLOCK,
    NAV_BLOCK_PICKUP
};

/* 
Array of the states needed to get from the leftmost industrial zone
to deliver to green and then go back to the start box */
static NAV_turns_e route_ind1_to_green_to_finish[] = {
    NAV_INDICATE_FOAM,
    NAV_BLIND_REVERSE,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_LEFT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS, // Four JUNC_PASS states used to travel far enough into start box
    NAV_JUNC_PASS, 
    NAV_JUNC_PASS,
    NAV_JUNC_PASS,
    NAV_END
};

/* 
Array of the states needed to get from the leftmost industrial zone
to deliver to red and then go back to the start box */
static NAV_turns_e route_ind1_to_red_to_finish[] = {
    NAV_INDICATE_SOLID,
    NAV_BLIND_REVERSE,
    NAV_JUNC_REVERSE_LEFT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_RIGHT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS,
    NAV_LINE_FOLLOW_FOR_TIME,
    NAV_BLOCK_DROPOFF,
    NAV_INIT_180_RIGHT,
    NAV_STOW_FLIPPER,
    NAV_COMPLETE_180_RIGHT,
    NAV_JUNC_CONFIRM,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_FORWARD_LEFT,
    NAV_LINE_FOLLOW,
    NAV_JUNC_PASS, // Four JUNC_PASS states used to travel far enough into start box
    NAV_JUNC_PASS, 
    NAV_JUNC_PASS,
    NAV_JUNC_PASS,
    NAV_END
};

// Declare variables to record which blocks have been delivered
static bool delivered_res1_block = false;
static bool delivered_res2_block = false;
static bool delivered_ind1_block = false;

// Create a pointer to a NAV_turns_e object and set it to point to the start of the route_start_to_res1 array
static const NAV_turns_e* current_turn_pos = route_start_to_res1;

// Function for using a custom array of states to execute, to make testing easier
void NAV_setup_custom_path(const NAV_turns_e* state_array_start) {
    delivered_res1_block = true;
    delivered_res2_block = true;
    delivered_ind1_block = true;
    current_turn_pos = state_array_start;
}

// Return the initial state to be executed
NAV_turns_e NAV_initial_state() {
    return *current_turn_pos;
}

// Function to return the next state given the exit condition of the previous state and using info about which blocks have been delivered
NAV_turns_e NAV_next_state(STATE_result_e result) {
    switch (result) {
        // If STATE_EXIT, simply go to the next state in the array
        case STATE_EXIT:
            // Increment the pointer
            current_turn_pos++;
            break;
        // If STATE_DETECTION_FOAM, deliver to green outpost
        case STATE_DETECTION_FOAM:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                // Make the pointer point to the first element of the new array
                current_turn_pos = route_res1_to_green_to_res2;
            }
            else if (!delivered_res2_block) {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_green_to_ind1;
            }
            else if (!delivered_ind1_block) {
                delivered_ind1_block = true;
                current_turn_pos = route_ind1_to_green_to_finish;
            }
            else { 
                // Custom path thinks all blocks are delivered so ends up here
                // Next state is just next element in the custom array so increment the pointer
                current_turn_pos++;
            }
            break;
        // If STATE_DETECTION_SOLID, deliver to red outpost
        case STATE_DETECTION_SOLID:
            if (!delivered_res1_block) {
                delivered_res1_block = true;
                current_turn_pos = route_res1_to_red_to_res2;
            }
            else if (!delivered_res2_block) {
                delivered_res2_block = true;
                current_turn_pos = route_res2_to_red_to_ind1;
            }
            else if (!delivered_ind1_block) {
                delivered_ind1_block = true;
                current_turn_pos = route_ind1_to_red_to_finish;
            }
            else {
                current_turn_pos++;
            }
            break;
        default:
            UTIL_error("Unexpected result passed to NAV_next: %i", result);
    }
    // Return the NAV_turns_e object that the pointer points to after going through the above process
    return *current_turn_pos;
}