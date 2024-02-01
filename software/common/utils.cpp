#include "utils.h"

#include "motor.h"

#define LOGGING_CHAR_COUNT 200

bool UTIL_reached_timeout(unsigned long start, unsigned long duration) {
    if (millis() - start < duration) {
        return false;
    }
    return true;
}

void UTIL_log(const char* format, ...) {
    char buf[LOGGING_CHAR_COUNT];

    unsigned long msecs, secs, mins;
    msecs = millis();
    secs = msecs / 1000;
    mins = secs / 60;
    secs %= 60;
    msecs %= 1000;

    size_t str_len = snprintf(buf, LOGGING_CHAR_COUNT, "%lu:%lu:%lu - ", mins, secs, msecs);

    va_list vl;
    va_start(vl, format);
    vsnprintf(buf + str_len, LOGGING_CHAR_COUNT - str_len, format, vl);
    va_end(vl);

    #ifdef USE_SERIAL
    Serial.print(buf);
    #endif
}

void UTIL_error(const char* format, ...) {
    char buf[LOGGING_CHAR_COUNT];

    va_list vl;
    va_start(vl, format);
    vsnprintf(buf, LOGGING_CHAR_COUNT, format, vl);
    va_end(vl);

    MOT_setspeeds(0, 0);

    while (true) {
        // TODO: flash LED
        #ifdef USE_SERIAL
        Serial.print(buf);
        #endif
    }
}