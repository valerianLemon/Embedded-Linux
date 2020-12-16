#include <stdlib.h>   // for atoi() and exit()
#include <unistd.h>   // for fork()
#include <sys/wait.h> // for waitpid()
#include <error.h>    // for errors
#include <stdio.h>

#include "../lib/Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"
#include "SharedMemory.h"

int main(int argc, char *argv[])
{
    int servSock;    /* Socket descriptor for server */
    int clntSock;    /* Socket descriptor for client */
    pid_t processID; /* Process ID from fork() */
    bool to_quit = false;

    parse_args(argc, argv);

    servSock = CreateTCPServerSocket(argv_port);

    create_shared_memory_object();

    while (to_quit == false) /* run until someone indicates to quit... */
    {
        clntSock = AcceptTCPConnection(servSock);
        printf("connected to: %d\n", getpid());

        processID = fork();
        if (processID < 0)
        {
            perror("faild to fork the process");
            exit(0); /* Child process terminates */
        }

        //Child process
        if (processID == 0)
        {
            printf("new fork\n");
            HandleTCPClient(clntSock);
            printf("end fork\n");
        }
    }

    // server stops...
    return (0);
}
