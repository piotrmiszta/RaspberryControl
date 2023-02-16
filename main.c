#include <stdio.h>
#include <stdlib.h>
#include "Include/Logger.h"
#include "Include/ClientInformations.h"
#include <time.h>
#include <unistd.h>

int main() {
    ClientInfo* client;
    logger_init("log.txt");
    LOG_DEBUG("Test debuga %s %s %d", __FILE__, __FUNCTION__, __LINE__);
    //starting logger thread
    client = client_searchClient("0c:c6:fd:ee:09:42");
    client_addClient(client);
    client_destroy(client);
    client = NULL;
    logger_destroy();
    return 0;
}
