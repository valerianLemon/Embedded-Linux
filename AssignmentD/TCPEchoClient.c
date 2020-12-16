#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define MAXMSGLENGTH 200   /* Max size of message */

int main (int argc, char *argv[])
{
    int         sock;                       /* Socket descriptor */
    char        chatString[MAXMSGLENGTH];   /* String to send to echo server */
    int         chatStringLen;              /* Length of string to echo */

    // Process arguments
    parse_args (argc, argv);

    // Create new sock
    sock = CreateTCPClientSocket (argv_ip, argv_port);   

    while (true)
    {
        // Take in string from user
        fgets(chatString, MAXMSGLENGTH-1, stdin); 

        // Store state
        int sentState = send(sock, chatString, MAXMSGLENGTH-1, 0);

        // Send this string to the server, with sock descriptor, buffer to store string in and specified length of string
        if (sentState > 0)
        { 
            // Wait for message to arrive
            while (true)
            {
                // If there is a message
                if (recv(sock, &chatString, MAXMSGLENGTH-1, 0) > 0)
                {
                    printf("\nReceived message: %s\n", chatString);      
                    break;                
                }
                // Reset chatBuffer                   
                memset(chatString, 0, MAXMSGLENGTH-1);

                // Wait for one second
                delaying();  

                // Show extra information in verbose mode
                info_s("accept", chatString);              
            }           
 
            sentState = -2;
            delaying ();
        }  
    }
    close (sock);
    info ("close & exit");
    exit (0);
}