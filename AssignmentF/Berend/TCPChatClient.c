#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <pthread.h>
#include <string.h>

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define MAXMSGLENGTH 200   /* Max size of message */

int         sock;                       /* Socket descriptor */
char        chatString[MAXMSGLENGTH];   /* String to send to echo server */
int         chatStringLen;              /* Length of string to echo */
pthread_t myThreadValue;
char username[50];

static void * myThread (void *);

int main (int argc, char *argv[])
{
    // Process arguments
    parse_args (argc, argv);

    // Create new sock
    sock = CreateTCPClientSocket (argv_ip, argv_port);   

    if (pthread_create (&myThreadValue, NULL, myThread, &sock) != 0)
    {
        perror ("Creation of myThread");
        exit(1);
    }

    printf("Dear kindred spirit. Please enter your username: ");
    fgets(username, 30, stdin);
    strcat(username, ": ");
    printf("%s", username);

    while (true)
    {
        /* If there is a message coming */
        if (recv(sock, &chatString, MAXMSGLENGTH-1, 0) > 0)
        {
            // print message
            printf("\nReceived message: %s\n", chatString);

            // Reset chatBuffer
            memset(chatString, 0, MAXMSGLENGTH-1);   
        }   
    }         
}

static void * myThread (void * sock)
{    
    while (true)
    {
        // Take in string from user
        fgets(chatString, MAXMSGLENGTH-1, stdin);  
        strtok(username, "\n");


        strcat(username, chatString);     

        // Store state
        int sentState = send(*(int*)sock, username, MAXMSGLENGTH-1, 0);  
    } 
}
   