#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>

#include "Auxiliary.h"
#include "HandleTCPClient.h"

#define RCVBUFSIZE 200   /* Size of receive buffer */

// Change lowercase characters to uppercase character
void swapCharacter (char* echoBuffer, int amountOfCharacters)
{
    for (size_t character = 0; character < amountOfCharacters; character++)
    {           
        char ch = *(echoBuffer + character);

        if (isupper(ch) && isalpha(ch))
        {
            *(echoBuffer + character) = tolower(ch);
        }
        else if (isalpha(ch)) *(echoBuffer + character) = toupper(ch);
    }
    // End array with EOS character
    *(echoBuffer + amountOfCharacters) = '\0';
}

void HandleTCPClient (int clntSocket)
{
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        // Print received data
        printf("\nReceived string from client: %s\n\n", echoBuffer);

        // TODO: add code to print the received string; use printf()        
        swapCharacter(echoBuffer, recvMsgSize);  

        delaying ();    
        
        /* Echo message back to client */
        if (send (clntSocket, echoBuffer, RCVBUFSIZE-1, 0) != recvMsgSize)
        {
            DieWithError ("send() failed");
        }

        memset (echoBuffer, 0, RCVBUFSIZE-1);
        // TODO: add code to display the transmitted string in verbose mode; use info_s()

        // receive next string
        recvMsgSize = recv (clntSocket, echoBuffer, RCVBUFSIZE-1, 0);
        if (recvMsgSize < 0)
        {
            DieWithError ("recv() failed");
        }
        info_d ("recv", recvMsgSize);

    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}
