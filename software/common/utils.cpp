#include "utils.h"

#include "motor.h"

#define SLEEP_STATE_MS 1000

static unsigned long start_ms;

void UTIL_reset_start_time() {
    start_ms = millis();
}

bool UTIL_reached_timeout(unsigned long duration) {
    if (millis() - start_ms < duration) {
        return false;
    }
    return true;
}

bool UTIL_sleep_loop() {
    return !UTIL_reached_timeout(SLEEP_STATE_MS);
}

#define LOGGING_CHAR_COUNT 200

static const char* log_level_strs[] = {
    "DEBUG",
    "INFO",
    "WARNING"
};

void UTIL_log(UTIL_log_e log_level, const char* format, ...) {
    if (log_level < LOG_LEVEL) {
        return;
    }

    char buf[LOGGING_CHAR_COUNT];

    unsigned long msecs, secs, mins;
    msecs = millis();
    secs = msecs / 1000;
    mins = secs / 60;
    secs %= 60;
    msecs %= 1000;

    size_t str_len = snprintf(buf, LOGGING_CHAR_COUNT, "%lu:%2lu:%3lu %s - ",
                              mins, secs, msecs, log_level_strs[log_level]);

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