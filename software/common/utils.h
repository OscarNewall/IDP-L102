#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// Comment out to disable logging to Serial
#define USE_SERIAL

// Safe macro to find array length - understanding unnecessary
#define ARRAY_SIZE(A) (sizeof(ArraySizeHelper(A)))

template <typename T, size_t N>
char (&ArraySizeHelper(T (&a)[N]))[N];

// Resets start time for timeout function
void UTIL_reset_start_time();

// Returns false until timeout reached - all times in ms
bool UTIL_reached_timeout(unsigned long duration);

bool UTIL_sleep_loop();

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING
} UTIL_log_e; // Keep upto date with log_level_strs in utils.cpp

#define LOG_LEVEL LOG_INFO

// log function to Serial with printf-style formatting, prefixed with time
void UTIL_log(UTIL_log_e log_level, const char* format, ...);

// Infinite loop with printf-style error message
void UTIL_error(const char* format, ...);


#endif