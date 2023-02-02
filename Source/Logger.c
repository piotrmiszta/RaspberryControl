#include "../Include/Logger.h"
typedef struct Logger{
    //FILE handler
    FILE* file;
    //Things to write
    const char* func;
    const char* fileDesc;
    int line;
    LogType type;
    const char* msg; //this arg will be set and printing by other thread
    va_list* list;
    //MUTEX for read/write and sem
    pthread_mutex_t mutex;
    sem_t semFull;
    sem_t semEmpty;
}Logger;

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
    fprintf(logger->file, "\n");

    pthread_mutex_init(&logger->mutex, NULL);
    sem_init(&logger->semEmpty,0 , 1);
    sem_init(&logger->semFull, 0, 0);
}
void logger_destroy() {
    fclose(logger->file);
    free(logger);
    logger = NULL;
}

void logger_log(LogType type, const char* file, const char* func, int line, const char* msg, ...) {
    sem_wait(&logger->semEmpty);
    pthread_mutex_lock(&logger->mutex);
    logger->type = type;
    logger->fileDesc = file;
    logger->func = func;
    logger->line = line;
    logger->msg = msg;
    va_list ap;
    va_start(ap,msg);
    logger->list = &ap;
    pthread_mutex_unlock(&logger->mutex);
    sem_post(&logger->semFull);
}
void logger_printTime() {
    time_t t;
    t = time(NULL);
    tzset();
    char datestr[51];
    strftime(datestr, sizeof(datestr) - 1, "%a %b %d %T %Z %Y", localtime(&t));
    fprintf(logger->file, "%s ", datestr);
}

void logger_print() {

    if(logger == NULL){
        fprintf(stderr, "%s - Line: %d function %s Logger is not initialization, first call logger_init\n", __FILE__, __LINE__, __FUNCTION__);
        return;
    }
    if(logger->file == NULL) {
        fprintf(stderr, "%s - Line: %d function %s Logger is not initialization, first call logger_init\n", __FILE__, __LINE__, __FUNCTION__);
        return;
    }

    switch (logger->type) {
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
    fprintf(logger->file, "LINE: %d ", logger->line);
    fprintf(logger->file, "FUNCTION: %s: \t", logger->func);

    vfprintf(logger->file, logger->msg, *(logger->list));
    va_end(*(logger->list));
    fprintf(logger->file, "\n");

}

void* logger_thread(void* arg) {
    while(1) {
        sem_wait(&logger->semFull);
        pthread_mutex_lock(&logger->mutex);
        logger_print();
        pthread_mutex_unlock(&logger->mutex);
        sem_post(&logger->semEmpty);
    }
}