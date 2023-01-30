#ifndef RASPBERRYCONTROL_LOGGER_H
#define RASPBERRYCONTROL_LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "Definitions.h"

typedef enum LogType{
    DEBUG,
    INFO,
    ERROR,
    WARNING,
    FATAL,
}LogType;

typedef struct Logger{
    FILE* file;
}Logger;

void logger_init(const char* filename);
void logger_log(LogType type, const char* file, const char* func, int line, const char* msg, ...);
void logger_destroy();
void logger_printTime();

#define LOG_DEBUG(msg, ...) logger_log(DEBUG, __FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__)
#define LOG_INFO(msg, ...) logger_log(INFO, __FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__)
#define LOG_ERROR(msg, ...) logger_log(ERROR, __FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__)
#define LOG_WARNING(msg, ...) logger_log(WARNING, __FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__)
#define LOG_FATAL(msg, ...) logger_log(FATAL, __FILE__, __FUNCTION__, __LINE__, msg, __VA_ARGS__)



#endif //RASPBERRYCONTROL_LOGGER_H