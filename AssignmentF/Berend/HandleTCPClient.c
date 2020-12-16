#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define MAXMSGLENGTH 200   /* Max size of message */

static void * myThread ();

char chatString[MAXMSGLENGTH];            /* String to send to echo server */
int  chatStringLen;                     /* Length of string to echo */
pthread_t myThreadValue;

void HandleTCPClient (int clntSocket)
{
    if (pthread_create (&myThreadValue, NULL, myThread, &clntSocket) != 0)
    {
        perror ("Creation of myThread");
        exit(1);
    }

    while (true)
    {
        /* If there is a message coming */
        if (recv(clntSocket, &chatString, MAXMSGLENGTH-1, 0) > 0)
        {
            // print message
            printf("%s", chatString);

            // Reset chatBuffer
            memset(chatString, 0, MAXMSGLENGTH-1);   
        }   
    }         
}

static void * myThread (void * clntSocket)
{    
    while (true)
    {
        // Take in string from user
        fgets(chatString, MAXMSGLENGTH-1, stdin);  

        // Store state
        int sentState = send(*(int*)clntSocket, chatString, MAXMSGLENGTH-1, 0);  
    } 
}
   

    //close (clntSocket);    /* Close client socket */
    //info ("close");

