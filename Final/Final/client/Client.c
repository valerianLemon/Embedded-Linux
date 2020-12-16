// Uploading a file
// 1. Client -> server = "DLESTXuploadDLEETX"
// 2. Client -> server = "DLESTXfilenameDLEETX"
// 3. Client -> server = "DLESTXsizeDLEETX"
// 4. Client -> server = "DLESTXsequence of bytesDLEETX"

// Downloading files
// 1. Client -> server = "DLESTXlistDLEETX"
// 2. Server -> client = "DLESTXf1@f2@f3DLEETX"
// 3. client -> server = "DLESTXfilenameDLEETX"
// 4. server -> client = "DLESTXsizeDLEETX"
// 5. Server -> client = "DLESTXsequence of bytesDLEETX"

#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "../lib/Auxiliary.h"
#include "CreateTCPClientSocket.h"
#include "MainMenu.h"
#include "Client.h"
#include "../lib/CommunicationProtocol.h"

/* current_state variable, keeping track of the current current_state */
STATE_T current_state;
STATE_T previous_state;

int idle()
{
    char port_number[PORT_SIZE];
    /* reserve 15 bytes for IP address */
    /* Get IP and port of server */
    printf("\nEnter server ip to connect to: \n");
    user_input(server_ip, IP_SIZE);
    /* Ask user for port */
    printf("Enter server port number: \n");
    return_value = user_input(port_number, PORT_SIZE);
    /* String conversion to short */
    server_port = (int)strtol(port_number, NULL, 0);

    /* Create server sock */
    sock = CreateTCPClientSocket(server_ip, server_port);

    printf("port number is: %d\n", server_port);

    printf("%s", "\nEnter name for client: ");
    /* Return value accordinly to success */
    return_value = user_input((char *)client_name, SERVER_MESSAGE_SIZE);
    /* Let server know client's name */
    if (send_message(sock, (char *)client_name, SERVER_MESSAGE_SIZE) == -1)
        return -1;

    return 1;
}

int running()
{
    /* Open menu in curses library */
    int menu_option = load_menu((char *)client_name);

    /* Go to state accorddingly to menu's return value */
    switch (menu_option)
    {
    case 0:
        current_state = LISTING;
        return menu_option;
    case 1:
        current_state = ENTERING_FILE;
        return menu_option;
    case 2:
        current_state = HELP;
        return menu_option;
    case 3:
        send_message (sock, EXIT, SERVER_MESSAGE_SIZE);
        exit(0);
    default:
        printf("Goto default\n");
        return -1;
    }
}

int user_input(char *ptr_to_message, int size)
{    /* Clean memory for message to receive */
    memset(ptr_to_message, 0, size);
    char* returned_string = fgets(ptr_to_message, size, stdin);
    if (strlen(returned_string) == 0) return -1;
    /* Remove newline character */
    remove_nl(ptr_to_message);

    return return_value;
}

int listing_files()
{
    /* Sent download request to server */
    if (send_message(sock, DOWNLOAD, SERVER_MESSAGE_SIZE) == -1)
        return -1;

    /* Wait for server file list */
    printf("Waiting for server reply with files...\n");
    if (receive_message(sock, message, SERVER_MESSAGE_SIZE) == -1)
        return -1;


    // TODO: Load menu where all the files are listed. Returns the selected filename (string)
    char *string = (char *)message;
    char **array = (char**)malloc(sizeof(char**)  * SERVER_MESSAGE_SIZE);
    int i = 0;

    array[i] = strtok(string, "@");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "@");
        printf("%s\n", array[i-1]);
    }

    // Wait for user to input filename (with file extension. N.B. .txt)
    printf("Enter filename with appropiate extension: ");
    return_value = user_input(file_name, FILE_NAME_SIZE);

    /* Send the actual filename to the server */
    if (send_message(sock, file_name, FILE_NAME_SIZE) == -1)
        return -1;

    return 1;
}

int downloading()
{
    file_size = 0;

    printf("Waiting for server reply with size of file to receive...\n");
    if (receive_message(sock, file_size_char, FILE_NAME_SIZE) == -1)
        return -1;
    file_size = atoi(file_size_char);

    /* Reserve size accordingly to file the server will sent */
    file_content = (char *)malloc(file_size * sizeof(char *));

    printf("Waiting for server reply with file content..\n");
    if (receive_message(sock, file_content, file_size) == -1)
        return -1;

    memset(file_path, 0, FILE_PATH_SIZE);
    printf("Enter file location to save file: ");
    return_value = user_input(file_path, FILE_PATH_SIZE);
    strcat (file_path, file_name);


    file_ptr = fopen(file_path, "w+");

    fwrite(file_content, sizeof(char), file_size, file_ptr);
    fclose(file_ptr);

    /* Make file content available memory again for next application */
    free(file_content);

    return 1;
}

int entering_file()
{
    if (send_message(sock, UPLOAD, SERVER_MESSAGE_SIZE) == -1)
        return -1;

    printf("Enter a name for the file that needs to be stored into the server: \n");
    return_value = user_input(file_name, FILE_NAME_SIZE);

    printf("Enter the path of the file on your PC: \n");
    return_value = user_input(file_path, FILE_PATH_SIZE);

    file_ptr = fopen(file_path, "r+");
    if (file_ptr == NULL)
    {
        perror("File could not be opened.");
        sleep(5);
        return -1;
    }

    if (send_message(sock, file_name, FILE_NAME_SIZE) == -1)
        return -1;

    // Get file size
    fseek(file_ptr, 0L, SEEK_END);
    file_size = ftell(file_ptr);
    fseek(file_ptr, 0L, SEEK_SET);

    // Convert file_size integer to a string
    memset(file_size_char, 0, FILE_NAME_SIZE);
    snprintf(file_size_char, FILE_NAME_SIZE, "%d", file_size);
    // Send file size
    if (send_message(sock, file_size_char, FILE_NAME_SIZE) == -1)
        return -1;

    return 1;
}

int uploading()
{
    /* Reserve memory for file to send dynamically */
    file_content = (char *)malloc(file_size * sizeof(char *));

    /* Store all bytes that are in concerning file in memory */
    int rtn = fread(file_content, sizeof(char), file_size, file_ptr);
    printf ("%d\n\n", rtn);

    // Send actual file contents
    if (send_message(sock, file_content, file_size) == -1)
        return -1;

    fclose(file_ptr);
    free(file_content);

    return 1;
}

int main(int argc, char *argv[])
{
    // Starting current_state of program is IDLE
    current_state = IDLE;
    previous_state = NONE;

    while (1)
    {
        switch (current_state)
        {
        case IDLE:
            if (previous_state != current_state)
            {
                previous_state = IDLE;
                // Goto 'running' state, if user has entered name
                if (idle() != EOF)
                {
                    current_state = RUNNING;
                }
            }
            break;
        case RUNNING:
            if (previous_state != current_state)
            {
                previous_state = RUNNING;
                int menu_option;
                if ((running()) == EOF)
                {
                    printf("Something went wrong with option %d. Please try again.", menu_option);
                }
            }
            break;
        case LISTING:
            if (previous_state != current_state)
            {
                previous_state = LISTING;
                if (listing_files() != EOF)
                {
                    current_state = DOWNLOADING;
                    break;
                }
                printf("Could not list files.");
                current_state = RUNNING;
            }
            break;
        case DOWNLOADING:
            if (previous_state != current_state)
            {
                previous_state = DOWNLOADING;
                if (downloading() != EOF)
                {
                    printf("Download success");
                    sleep(1);
                }
                else
                    printf("Download failure");
                current_state = RUNNING;
            }
            break;
        case UPLOADING:
            if (previous_state != current_state)
            {
                previous_state = UPLOADING;
                if (uploading() != EOF)
                {
                    printf("Upload success");
                    sleep(1);
                }
                else
                    printf("Upload failure");
                current_state = RUNNING;
            }
            break;
        case ENTERING_FILE:
            if (previous_state != current_state)
            {
                previous_state = ENTERING_FILE;
                if (entering_file() != EOF)
                {
                    current_state = UPLOADING;
                    break;
                }
                current_state = RUNNING;
            }
            break;
        case HELP:
            /* code */
            break;

        default:
            break;
        }
    }
    return 0;
}