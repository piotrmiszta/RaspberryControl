#ifndef RASPBERRYCONTROL_LOGGER_H
#define RASPBERRYCONTROL_LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "Definitions.h"

typedef enum LogType{
    DEBUG,
    INFO,
    ERROR,
    WARNING,
    FATAL,
}LogType;

typedef struct Logger Logger;

void logger_init(const char* filename);
void logger_log(LogType type, const char* file, const char* func, int line, const char* msg, ...); //THIS FUNCTION WILL BE SETTING STRUCT
void logger_destroy();
void logger_printTime();

#define LOG_DEBUG(...)     logger_log(DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)      logger_log(INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)     logger_log(ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...)   logger_log(WARNING, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...)     logger_log(FATAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)



#endif //RASPBERRYCONTROL_LOGGER_H