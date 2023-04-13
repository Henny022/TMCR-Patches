#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef enum LogLevel{
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
} LogLevel;

int mgba_debug_enable();

void mgba_print(LogLevel level, const char* s);

#ifdef __cplusplus
}
#endif
