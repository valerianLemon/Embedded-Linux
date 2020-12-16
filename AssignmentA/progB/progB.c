/*
    Embedded Linux assignment 1B

    Written by Valerian Mirzac.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <getopt.h>


static int  shm_fd = -1;

// Check all passed arguments that user passed to function when executing
int evaluateAndStoreFunctionArguments (int argc, char** argv, char** flag_name)
{
    int opt = 0;

    // when 'getopt' does not return -1, continue
    while ((opt = getopt(argc, argv, "hr:s:f:")) != -1) 
    {
        // Evaluate individual flags
        switch(opt) 
        {
            case 'h':
                printf("\nEmbedded linux, assignment A. \n\nMandatory flags are: \n{-s [SIZE OF SHM IN BYTES]}\n{-r [AMOUNT OF TIMES PROGRAM SHOULD REPEAT]}\n{-f [SHARED MEMORY NAME]}\n\n");
                return -1;
                break;
            case 'f':
                *flag_name = optarg;
                break;
                // Check other options
            case '?':
                if (optopt == 'f') fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    // Evaluate whether all flags are valid 
    if (*flag_name == NULL) 
    {
        printf("\nname is missing\n");
        return -1;
    }
}

void open_shm(char* shm_name, int* size, void** shm_address)
{
    int shm_s;
    int *shm_a;

    shm_fd = shm_open(shm_name, O_RDWR, 0600);
    if(shm_fd == -1)
    {
        perror("ERROR: shm_open() failed\n");
    }
    printf("shm_open returned %d\n", shm_fd);

    shm_s = lseek(shm_fd, 0, SEEK_END);
    *size = shm_s;
    printf("lseek returned %d\n", shm_s);

    *shm_address = mmap (NULL, shm_s, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_address == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }
    printf("mmap returned %p\n", shm_address);
}

int main(int argc, char *argv[])
{
    int size;
    void *shm_addr;
    char buf = 'A';
    char* name = NULL;

    // Only continue when all flags are pared correctly
    if (!evaluateAndStoreFunctionArguments(argc, argv, &name)) return -1;
    
    //open shared memory and 
    open_shm(name, &size, &shm_addr);

    if(*(char*)shm_addr == 'a')
    {
        memcpy(shm_addr, &buf, 1);
    }
}
