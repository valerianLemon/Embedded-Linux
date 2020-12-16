#include <pthread.h>
#include <stdio.h>

#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"

static void * myThread (void* arg);            /* thread that does the work */

int main (int argc, char *argv[])
{
    int         servSock;     /* Socket descriptor for server */
    int         clntSock;     /* Socket descriptor for client */
    pthread_t   threadID;     /* Thread ID from pthread_create() */
    bool        to_quit = false;

    parse_args (argc, argv);

    servSock = CreateTCPServerSocket (argv_port);

    while (to_quit == false)             
    {
        clntSock = AcceptTCPConnection (servSock);

        pthread_t myThreadValue;

        if (pthread_create (&myThreadValue, NULL, myThread, &clntSock) != 0)
        {
            perror ("Creation of myThread");
        }     
    }    
	return (0);
}

static void * myThread (void* clntSock)
{    

    HandleTCPClient (*(int*)clntSock);
    pthread_detach(pthread_self());

    return (NULL);
}
