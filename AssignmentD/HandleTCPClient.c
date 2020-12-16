#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define MAXMSGLENGTH 200   /* Max size of message */

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()
    char chatString[MAXMSGLENGTH];            /* String to send to echo server */
    int  chatStringLen;                     /* Length of string to echo */

    while (true)
    {
    /* If there is a message coming */
    if (recv(clntSocket, &chatString, MAXMSGLENGTH-1, 0) > 0)
    {
        // print message
        printf("\nReceived message: %s\n", chatString);

        // Reset chatBuffer
        memset(chatString, 0, MAXMSGLENGTH-1);   

        while (true)
        {
            // Take in string from user
            fgets(chatString, MAXMSGLENGTH-1, stdin);       

            // Store state
            int sentState = send(clntSocket, chatString, MAXMSGLENGTH-1, 0);

            if (sentState > 0)
            {
                // Break out of loop
                break;
            }
        }        
    }    
    }
    

    close (clntSocket);    /* Close client socket */
    info ("close");
}
