#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <getopt.h>

#ifndef LOG_SERVER_ACTIVITY_H
#define LOG_SERVER_ACTIVITY_H

#define LOG_CONNECT 0
#define LOG_UPLOAD 1
#define LOG_DOWNLOAD 2
#define LOG_FILE_TO_DOWNLOAD 3
#define LOG_FILE_TO_UPLOAD 4
#define LOG_LIST_SERVER_FILES 5

#define LOG_TIMESTAMP_LEANTH 25
#define MAX_LOG_MESSAGE_LEANTH 255
#define MAX_CLIENT_NAME_LEANTH 100

void WriteToLogFile(char *client_name, char *record, int flag);

#endif
