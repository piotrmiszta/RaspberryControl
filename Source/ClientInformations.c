#include "../Include/ClientInformations.h"

#define NAME_LEN    24
#define DIR_LEN     24
#define LOGIN_LEN   24
#define PASS_LEN    24
#define MAC_LEN     18      //xx:xx:xx:xx:xx:xx/0

typedef struct ClientInformation {
    char mac[MAC_LEN];
    char name[NAME_LEN];
    char directory[DIR_LEN];
    char login[LOGIN_LEN];
    char pass[PASS_LEN];
    unsigned short int root;
}ClientInformation;


int client_checkString(FILE* file, const char* string);

ClientInfo* client_getClient(FILE* file, const char* macAddresss) {
    ClientInfo * client = NULL;

    client = malloc(sizeof(ClientInfo));
    if(client == NULL) {
        fprintf(stderr, "%s: %d: Cant allocate for client info", __FUNCTION__ , __LINE__);
        LOG_ERROR("Cant allocate for client info");
        return NULL;
    }
    if(file == NULL) {
        fprintf(stderr, "%s: %d: Cant open file date", __FUNCTION__, __LINE__);
        LOG_ERROR("Cant open DATE file");
        return NULL;
    }
    strcpy(client->mac, macAddresss);
    if(client_checkString(file, "{\0") == false) {
        free(client);
        return NULL;
    }
    if(client_checkString(file, "name:\0") == false) {
        free(client);
        return NULL;
    }
    fscanf(file, "%s", client->name);
    if(client_checkString(file, "directory:\0") == false) {
        free(client);
        return NULL;
    }
    fscanf(file, "%s", client->directory);
    if(client_checkString(file, "root:\0") == false) {
        free(client);
        return NULL;
    }
    fscanf(file, "%hu", &client->root);
    if(client_checkString(file, "login:\0") == false) {
        free(client);
        return NULL;
    }
    fscanf(file, "%s", client->login);
    if(client_checkString(file, "pass:\0") == false) {
        free(client);
        return NULL;
    }
    fscanf(file, "%s", client->pass);
    if(client_checkString(file, "}\0") == false) {
        free(client);
        return NULL;
    }
    return client;
}

int client_checkString(FILE* file, const char* string) {
    char temp[255];
    fscanf(file, "%s", temp);
    if(strcmp(temp, string) != 0) {
        fprintf(stderr, "Data file is corrupt");
        LOG_ERROR("Data file is corrupt");
        return false;
    }
    return true;
}

ClientInfo* client_searchClient(const char* macAddress) {
    ClientInfo* client = NULL;
    FILE* file = fopen("../data.txt", "r");
    if(file == NULL) {
        fprintf(stderr, "%s: %d: Cant open file date", __FUNCTION__, __LINE__);
        LOG_ERROR("Cant open DATE file");
        return NULL;
    }
    while(!feof(file)) {
        char temp[MAC_LEN];
        fscanf(file, "%s", temp);
        if(strcmp(temp, macAddress) == 0) {
            LOG_INFO("Find MAC %s", macAddress);
            client = client_getClient(file, temp);
            break;
        }
        else {
            char k[255];
            for(int i = 0; i < 12; ++i)
                if(fscanf(file, "%s", k) == EOF){
                    LOG_INFO("Didnt find MAC %s", macAddress);
                    fclose(file);
                    return NULL;
                }
        }
    }
    fclose(file);
    return client;
}

int client_addClient(const ClientInfo* client) {
    FILE* file;

    if(client == NULL) {
        fprintf(stderr, "%s: %d: Client is null pointer", __FUNCTION__, __LINE__);
        LOG_ERROR("Client is null pointer");
        return E_ARG;
    }
    file = fopen("../data2.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "%s: %d: Cant open file date", __FUNCTION__, __LINE__);
        LOG_ERROR("Cant open DATE file");
        return E_FAIL;
    }
    fprintf(file, "\n");
    fprintf(file, "%s\n", client->mac);
    fprintf(file, "{\n");
    fprintf(file, "\tname: %s\n", client->name);
    fprintf(file, "\tdirectory: %s\n", client->directory);
    fprintf(file, "\troot: %u\n", client->root);
    fprintf(file, "\tlogin: %s\n", client->login);
    fprintf(file, "\tpass: %s\n", client->pass);
    fprintf(file, "}");
    fclose(file);
    LOG_INFO("Added new client with %s mac address into data", client->mac);
    return SUCCESS;
}

int client_clientCmp(const ClientInfo* client, const ClientInfo* client2) {
    if(client == NULL && client2 == NULL) {
        fprintf(stderr, "%s: %d: Client or client2 is null pointer", __FUNCTION__, __LINE__);
        LOG_ERROR("Client or client2 is null pointer");
        return E_ARG;
    }

    if(client->mac == client2->mac && client->login == client2->login) {
        if(client->directory == client2->directory && client->pass == client2->pass) {
            if(client->name == client2->name && client->root == client2->root) {
                return 1;
            }
        }
    }
    return 0;
}

void client_destroy(ClientInfo* client) {
    free(client);
}
