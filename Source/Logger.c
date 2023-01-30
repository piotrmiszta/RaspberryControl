//
// Created by programowanie on 30.01.23.
//
#include "../Include/Logger.h"
Logger* logger = NULL;

void logger_init(const char* filename) {
    logger = malloc(sizeof(Logger));
    if(logger == NULL) {
        fprintf(stderr, "%s - Line: %d: function %s: Can't alloc", __FILE__, __LINE__, __FUNCTION__ );
        exit(1);
    }
    else{
        logger->file = fopen(filename, "w");
        if(logger->file == NULL) {
            fprintf(stderr, "%s - Line: %d function %s: Can't open %s file\n", __FILE__, __LINE__, __FUNCTION__, filename );
            exit(1);
        }
    }
    fprintf(logger->file, "LOG FILE AUTOMATICLY CREATED \n");
    logger_printTime();
    fprintf(logger->file, "\n%s\n", NAME);
    fprintf(logger->file, "AUTHOR: %s\n", AUTHOR);
    fprintf(logger->file, "VERSION: %s\n", VERSION);
    fprintf(logger->file, "\n", VERSION);
}
void logger_destroy() {
    fclose(logger->file);
    free(logger);
    logger = NULL;
}
void logger_log(LogType type, const char* file, const char* func, int line, const char* msg, ...) {
    if(logger == NULL){
        fprintf(stderr, "%s - Line: %d function %s Logger is not initialization, first call logger_init\n", __FILE__, __LINE__, __FUNCTION__);
        return;
    }
    if(logger->file == NULL) {
        fprintf(stderr, "%s - Line: %d function %s Logger is not initialization, first call logger_init\n", __FILE__, __LINE__, __FUNCTION__);
        return;
    }

    switch (type) {
        case DEBUG:
            fprintf(logger->file, "[DEBUG] ");
            break;
        case INFO:
            fprintf(logger->file, "[INFO] ");
            break;
        case WARNING:
            fprintf(logger->file, "[WARNING] ");
            break;
        case ERROR:
            fprintf(logger->file, "[ERROR] ");
            break;
        case FATAL:
            fprintf(logger->file, "[FATAL] ");
            break;
    }
    logger_printTime();
#ifndef NO_FILE
    fprintf(logger->file, "FILE: %s ", file);
#endif //NO_FILE
    fprintf(logger->file, "LINE: %d ", line);
    fprintf(logger->file, "FUNCTION: %s: \t", func);

    va_list ap;
    va_start(ap, msg);
    vfprintf(logger->file, msg, &ap);
    va_end(ap);
    fprintf(logger->file, "\n");
}
void logger_printTime() {
    time_t t;
    t = time(NULL);
    tzset();
    char datestr[51];
    strftime(datestr, sizeof(datestr) - 1, "%a %b %d %T %Z %Y", localtime(&t));
    fprintf(logger->file, "%s ", datestr);
}
