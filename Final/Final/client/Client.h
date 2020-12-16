#ifndef TCPEchoClient
#define TCPEchoClient

#define IP_SIZE 16
#define PORT_SIZE 255

/* Socket descriptor for server communication */
int sock;
int server_port;
char server_ip[IP_SIZE];
int  return_value;
FILE *file_ptr;

/* All the current_states */
typedef enum
{
    IDLE,
    RUNNING,
    LISTING,
    DOWNLOADING,
    UPLOADING,
    ENTERING_FILE,
    HELP,
    NONE
} STATE_T;

// List of files that are being sent by the server
//extern char* server_message;

int user_input (char* ptr_to_message, int size);
int idle();
int running();
int listing_files();
int entering_file ();
int uploading ();
int downloading();

#endif