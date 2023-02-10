#ifndef RASPBERRYCONTROL_CLIENTINFORMATIONS_H
#define RASPBERRYCONTROL_CLIENTINFORMATIONS_H
#include <stdlib.h> //allocating
#include <stdio.h>  //file stderr, stdio
#include <string.h> //strcpy, strcmp

#include "Definitions.h"
#include "Logger.h"

typedef struct ClientInformation ClientInfo;
/**
 * Struct for handling info from data file
 * Each client have the same info which can be empty
 * */


ClientInfo* client_getClient(FILE* file, const char* macAddress);
/**
 * Geting one client info from ../data file
 * Returning pointer to struct ClientInfo if completed
 * or NULL if error
 */


ClientInfo* client_searchClient(const char* macAddress);
/**
 * Searching for client in ../data file, setting a FILE* pointer to position on end of mac address of searching client
 * Returning pointer to struct ClientInfo if completed
 * or NULL if error
 */


int client_addClient(const ClientInfo* client);
/**
 * Adding to end file ../data, info about client
 * Returning SUCCESS if its done or E_XXX if error
 */


int client_clientCmp(const ClientInfo* client, const ClientInfo* client2);
/**
 * Compare two clients
 * Returning positive int >0 if equal
 * 0 if not equal
 * negative <0 integers if error
 */


void client_destroy(ClientInfo* client);
/**
 * DESTRUCTOR FOR CLIENT MUST BE ALWAYS CALL ON EACH CLIENT BY THE END PROGRAM
 */

#endif //RASPBERRYCONTROL_CLIENTINFORMATIONS_H
