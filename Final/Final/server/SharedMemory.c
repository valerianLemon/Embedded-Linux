#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "../lib/Auxiliary.h"
#include "SharedMemory.h"

#define SHM_SIZE 10000

int shm_fd;
int size;
int total_size_content = 0;
void *shm_addr;
char *name = "files", *content;

void create_shared_memory_object()
{
    content = (char*) malloc (10000 * sizeof (char*));
    // create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // configure the size of the shared memory object
    int trn = ftruncate(shm_fd, SHM_SIZE);
    printf("%d", trn);

    // memory map the shared memory object
    shm_addr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    list_files_initially();
}

void add_to_shard_memory(char *file_name_to_add)
{
    strcat(content, file_name_to_add);
    strcat(content, "@");
    memset(shm_addr, 0, SHM_SIZE);
    memcpy(shm_addr, content, SHM_SIZE);
}

void list_files_initially()
{
    struct dirent *de;
    DIR *dr = opendir("../files/");

    if (dr == NULL)
    {
        perror("Could not open current directory");
    }

    while ((de = readdir(dr)) != NULL)
    {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
        {
            add_to_shard_memory(de->d_name);
        }
    }
    closedir(dr);

    
}