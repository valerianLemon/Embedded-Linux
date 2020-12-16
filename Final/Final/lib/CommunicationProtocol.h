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

#ifndef _COMUNICATION_PROTOCOL_H_
#define _COMUNICATION_PROTOCOL_H_

#define FILE_NAME_SIZE 255
#define FILE_PATH_SIZE 4096
#define SERVER_MESSAGE_SIZE 10000

#define DOWNLOAD "download"
#define UPLOAD "upload"
#define EXIT "exit"

int file_size;
char client_name[SERVER_MESSAGE_SIZE];
char file_name[FILE_NAME_SIZE];
char file_size_char[FILE_NAME_SIZE];
char message[SERVER_MESSAGE_SIZE];
char file_path[FILE_PATH_SIZE];
char* file_content;

int receive_message(int sock, char *message_to_receive, int size);
int send_message(int sock, char *message_to_send, int size);


#endif