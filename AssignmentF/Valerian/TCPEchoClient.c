#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 200   /* Size of receive buffer */

int main (int argc, char *argv[])
{
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[RCVBUFSIZE]; /* Buffer for received string */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */
    int         i;                      /* counter for data-arguments */

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);
        
    for (i = 0; i < argv_nrofdata; i++)
    {
        echoString = argv_data [i];            /* Store input string of user to later process */
        echoStringLen = strlen (echoString);          /* Determine input length and store in echoStringLen */

        // Wait for one second
        delaying();        

        // Send this string to the server, with sock descriptor, buffer to store string in and specified length of string
        send(sock, echoString, RCVBUFSIZE-1, 0);

        // TODO: add code to display the transmitted string in verbose mode; use info_s()
        info_s("accept", echoString);

        // Receive incoming data
        bytesRcvd = recv(sock, &echoBuffer, RCVBUFSIZE-1, 0);
        
        // Print received data
        printf("\nReceived string from server: %s\n\n", echoBuffer);

        // Clear buffer
        memset (echoBuffer, 0, RCVBUFSIZE-1);
    }

    delaying ();

    close (sock);
    info ("close & exit");
    exit (0);
}
