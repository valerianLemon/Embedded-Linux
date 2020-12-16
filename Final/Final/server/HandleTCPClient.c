#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "../lib/Auxiliary.h"
#include "HandleTCPClient.h"
#include "../lib/CommunicationProtocol.h"
#include "SharedMemory.h"
#include <semaphore.h>

bool stop_client = false;

int uploadToServer(int clntSocket)
{
    sem_t *sem_addr_temp = SEM_FAILED;
    return_value = receive_message(clntSocket, message, FILE_NAME_SIZE);

    memset(file_name, 0, FILE_NAME_SIZE);
    strcpy(file_name, message);
    printf("file name: %s\n", file_name);

    //add_to_shard_memory (file_name);
    //Set semaphore for the file
    sem_addr_temp = CreateFileSemaphore(file_name);
    sem_wait(sem_addr_temp);

    memset(file_path, 0, FILE_PATH_SIZE);
    strcpy(file_path, "../files/");
    strcat(file_path, file_name);
    printf("File path to file: %s\n", file_path);

    return_value = receive_message(clntSocket, message, FILE_NAME_SIZE);
    file_size = atoi(message);
    printf("file size: %d\n", file_size);

    file_content = (char *)malloc(file_size * sizeof(char *));
    return_value = receive_message(clntSocket, file_content, file_size);

    file_ptr = fopen(file_path, "w+");
    fwrite(file_content, sizeof(char), file_size, file_ptr);

    fclose(file_ptr);
    free(file_content);
    file_size = 0;
    sem_post(sem_addr_temp);

    return 1;
}

int downloadFromServer(int clntSocket)
{
    sem_t *sem_addr_temp = SEM_FAILED;
    printf("List: %s\n\n", (char *)shm_addr);
    printf("1\n");
    send_message(clntSocket, shm_addr, SERVER_MESSAGE_SIZE);
    printf("2\n");
    memset(file_path, 0, FILE_PATH_SIZE);
    //Read file name and create file path
    strcpy(file_path, "../files/");
    return_value = receive_message(clntSocket, message, FILE_NAME_SIZE);
    strcpy(file_name, message);
    strcat(file_path, file_name);
    printf("File path to file: %s\n", file_path);
    printf("3\n");
    //Set semaphore for the file
    sem_addr_temp = CreateFileSemaphore(file_name);
    printf("4\n");
    sem_wait(sem_addr_temp);
    printf("5\n");
    //Send file size
    file_ptr = fopen(file_path, "r+");
    if (file_ptr == NULL)
    {
        perror("File could not be opened.");
        return -1;
    }
    //add_to_shard_memory(file_name);
    printf("6\n");
    // Get file size
    fseek(file_ptr, 0L, SEEK_END);
    file_size = ftell(file_ptr);
    fseek(file_ptr, 0L, SEEK_SET);

    // Convert file_size integer to a string
    memset(file_size_char, 0, FILE_NAME_SIZE);
    snprintf(file_size_char, FILE_NAME_SIZE, "%d", file_size);
    // Send file size
    if (send_message(clntSocket, file_size_char, FILE_NAME_SIZE) == -1)
        return -1;

    /* Reserve memory for file to send dynamically */
    file_content = (char *)malloc(file_size * sizeof(char *));

    /* Store all bytes that are in concerning file in memory */
    return_value = fread(file_content, sizeof(char), file_size, file_ptr);

    // Send actual file contents
    if (send_message(clntSocket, file_content, file_size) == -1)
        return -1;

    printf("7\n");
    fclose(file_ptr);
    free(file_content);
    sleep(10);
    sem_post(sem_addr_temp);
    printf("8\n");

    return 1;
}

void HandleTCPClient(int clntSocket)
{
    SERVER_STATE_T server_state = IDLE;
    create_shared_memory_object();

    //read client name
    if (recv(clntSocket, message, SERVER_MESSAGE_SIZE, 0) > 0)
    {
        printf("client_msg: '%s' ,check 1\n", message);
        strcpy(client_name, message);
        memset(message, 0, SERVER_MESSAGE_SIZE);
    }

    while (1)
    {
        switch (server_state)
        {
        case IDLE:
            if (recv(clntSocket, message, SERVER_MESSAGE_SIZE, 0) > 0)
            {
                //Uploading to server
                if (strcmp(message, UPLOAD) == 0)
                {
                    printf("client wants to: '%s'\n", message);
                    memset(message, 0, SERVER_MESSAGE_SIZE);
                    server_state = SERVER_UPLOAD;
                }

                //Download from server
                if (strcmp(message, DOWNLOAD) == 0)
                {
                    printf("client wants to: '%s'\n", message);
                    memset(message, 0, SERVER_MESSAGE_SIZE);
                    server_state = SERVER_DOWNLOAD;
                }

                //End process client
                if (strcmp(message, EXIT) == 0)
                {
                    printf("client wants to: '%s'\n", message);
                    memset(message, 0, SERVER_MESSAGE_SIZE);
                    server_state = QUIT;
                }
            }

            break;
        case SERVER_UPLOAD:
            uploadToServer(clntSocket);
            server_state = IDLE;
            break;
        case SERVER_DOWNLOAD:
            downloadFromServer(clntSocket);
            server_state = IDLE;
            break;
        case HELP:
            /* code */
            break;
        case QUIT:
            //stop_client = false;
            break;
        default:
            break;
        }
    }
    /*
    //Check ir client wants to upload or download
    if (recv(clntSocket, message, SERVER_MESSAGE_SIZE, 0) > 0)
    {
        //Uploading to server
        if (strcmp(message, UPLOAD) == 0)
        {
            printf("client wants to: '%s'\n", message);
            memset(message, 0, SERVER_MESSAGE_SIZE);
            uploadToServer(clntSocket);
        }

        //Download from server
        if (strcmp(message, DOWNLOAD) == 0)
        {
            printf("client wants to: '%s'\n", message);
            memset(message, 0, SERVER_MESSAGE_SIZE);
            downloadFromServer(clntSocket);
        }
    }
    */
    close(clntSocket); /* Close client socket */
    info("close");
}