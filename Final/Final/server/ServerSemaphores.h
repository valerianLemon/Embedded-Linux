#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>

#ifndef SERVER_SEMAPHORES_H
#define SERVER_SEMAPHORES_H

sem_t *sem_addr;
mode_t umask_value;
char line[80];
char sem_name[80];
char number_value[5];
int value;
int permissions;
int choice;
int rtnval;
int combined;
int groupPermission;
int otherPermission;

sem_t* CreateFileSemaphore(char * file_name);

#endif