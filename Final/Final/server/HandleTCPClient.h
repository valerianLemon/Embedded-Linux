#include "../lib/CommunicationProtocol.h"
#include "ServerSemaphores.h"
#include <fcntl.h>
#include <stdlib.h>

#ifndef _HANDLE_TCP_CLIENT_H_
#define _HANDLE_TCP_CLIENT_H_

#define MAX_FILES_IN_SERVER 100

void HandleTCPClient(int clntSocket); /* TCP client handling function */
void swapCharacter(char *echoBuffer, int amountOfCharacters);

int return_value;
char filesList[ FILE_NAME_SIZE * (MAX_FILES_IN_SERVER + 1)];

FILE *file_ptr;

//Server states
typedef enum
{
    IDLE,
    SERVER_UPLOAD,
    SERVER_DOWNLOAD,
    HELP,
    QUIT
} SERVER_STATE_T;

#endif
