#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_ESP)
#include <cstdint>

/** this print is some deep information for debug purpose */
#define TRACE_LEVEL_DEBUG         0x10
/** Info print, for general purpose prints */
#define TRACE_LEVEL_INFO          0x08
/** warning prints, which shouldn't causes any huge problems */
#define TRACE_LEVEL_WARN          0x04
/** Error prints, which causes probably problems, e.g. out of mem. */
#define TRACE_LEVEL_ERROR         0x02

void mbed_tracef(uint8_t dlevel, const char *grp, const char *fmt, ...) __attribute__((__format__(__printf__, 3, 4)));

#define tr_info(...)            mbed_tracef(TRACE_LEVEL_INFO,    TRACE_GROUP, __VA_ARGS__)   //!< Print info message
#define tr_warning(...)         mbed_tracef(TRACE_LEVEL_WARN,    TRACE_GROUP, __VA_ARGS__)   //!< Print warning message
#define tr_debug(...)           mbed_tracef(TRACE_LEVEL_DEBUG,   TRACE_GROUP, __VA_ARGS__)   //!< Print debug message
#define tr_error(...)           mbed_tracef(TRACE_LEVEL_ERROR,   TRACE_GROUP, __VA_ARGS__)   //!< Print Error Message

// ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);

// define TAG
// define tr_error ESP_LOGE(TRACE_GROUP,


#endif

#if defined(PLATFORM_MBED)
#include "mbed_trace.h"
#endif