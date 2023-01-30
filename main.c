#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Include/Logger.h"
int main() {
    logger_init("test.log");
    char* test = "suema";
    LOG_DEBUG("Debug %s", test);
    LOG_WARNING("warning %s", test);
    LOG_ERROR("error %s", test);
    LOG_FATAL("fatal %s", test);
    LOG_INFO("info %s", test);

    logger_destroy();
    return 0;
}