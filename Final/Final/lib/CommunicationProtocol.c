#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include "CommunicationProtocol.h"

int return_value;

int receive_message(int sock, char *message_to_receive, int size)
{
    /* Clear message buffer */
    memset(message_to_receive, 0, size);
    /* Store return vale to evaluate success */
    if ((return_value = recv(sock, message_to_receive, size, 0)) > 0)
    {
        if (return_value == -1)
        {
            perror("Rerv server error");
            return -1;
        }
    }
    return 1;
}

int send_message(int sock, char *message_to_send, int size)
{
    /* Reserve memory for "message_to_send" */
    memset(message, 0, size);
    strcpy(message, message_to_send);

    /* Store return vale to evaluate success */
    if ((return_value = send(sock, message, size, 0)) > 0)
    {
        if (return_value == -1)
        {
            perror("Send error");
            return -1;
        }
    }
    return 1;
}