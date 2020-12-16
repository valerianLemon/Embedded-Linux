#include "ServerSemaphores.h"

sem_t* CreateFileSemaphore(char *file_name)
{
    strcpy(sem_name, file_name);
    sem_addr = sem_open(sem_name, O_CREAT, 0600, 1);
    return sem_addr;
}


