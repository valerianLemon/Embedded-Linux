#include "LogServerActivity.h"

time_t *record_time;

FILE *file_ptr;
char *logfile_path = "../logs/log.txt";
char record[LOG_TIMESTAMP_LEANTH + MAX_CLIENT_NAME_LEANTH + MAX_LOG_MESSAGE_LEANTH];

void WriteToLogFile(char *client_name, char *file_name, int flag)
{
    char *time_stamp = ctime(&record_time);

    int len;

    len = strlen(time_stamp);
    if (time_stamp[len - 1] == '\n')
    {
        time_stamp[len - 1] = '\0';
    }
    strcat(record, "[");
    strcat(record, time_stamp);
    strcat(record, "] ");
    strcat(record, client_name);
    switch (flag)
    {
    case LOG_CONNECT:
        strcat(record, " client has connected to server");
        break;
    case LOG_UPLOAD:
        strcat(record, " wants to upload a file to the server");
        break;
    case LOG_DOWNLOAD:
        strcat(record, " wants to download from the server");
        break;
    case LOG_FILE_TO_DOWNLOAD:
        strcat(record, " wants to download '");
        strncat(record, file_name, MAX_LOG_MESSAGE_LEANTH);
        strcat(record, "' from the server");
        break;
    case LOG_FILE_TO_UPLOAD:
        strcat(record, " wants to upload '");
        strncat(record, file_name, MAX_LOG_MESSAGE_LEANTH);
        strcat(record, "' to the server");
        break;
    case LOG_LIST_SERVER_FILES:
        strcat(record, " requests file list");
        break;
    default:
        strcat(record, " wrong flag");
        break;
    }
    strcat(record, "\n");

    file_ptr = fopen(logfile_path, "a+");

    fwrite(record, sizeof(char), strlen(record), file_ptr);
}

void signal_handler(int sig)
{
    
}


int main()
{
    WriteToLogFile("client1", "data.txt",LOG_FILE_TO_DOWNLOAD);
    return 0;
}