#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// Comment out to disable logging to Serial
#define USE_SERIAL

// Safe macro to find array length - understanding unnecessary
#define ARRAY_SIZE(A) (sizeof(ArraySizeHelper(A)))

template <typename T, size_t N>
char (&ArraySizeHelper(T (&a)[N]))[N];

// log function to Serial with printf-style formatting
void UTIL_log(const char* format, ...);

// Infinite loop with printf-style error message
void UTIL_error(const char* format, ...);

#endif