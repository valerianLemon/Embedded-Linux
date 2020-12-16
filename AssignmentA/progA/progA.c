/*
    Embedded Linux assignment 1A

    Written by Berend van Schaik.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <getopt.h>

// Check all passed arguments that user passed to function when executing
int evaluateAndStoreFunctionArguments (int argc, char** argv, int* flag_r, int* flag_s, char** flag_name)
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
            case 'r':
                *flag_r = atoi(optarg);
                break;
            case 's':
                *flag_s = atoi(optarg);
                break;
            case 'f':
                *flag_name = optarg;
                break;
                // Check other options
            case '?':
                if (optopt == 'r') fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                if (optopt == 's') fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    // Evaluate whether all flags are valid 
    if (*flag_r == -1 || *flag_s == -1 || flag_name == NULL) 
    {
        printf("\n-r, -f or -s is missing\n");
        return -1;
    }
}

void createSharedMemoryObject(int shm_fd, void** ptr, char* name, int SIZE, char* content)
{
    // create the shared memory object 
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

    // configure the size of the shared memory object
    ftruncate(shm_fd, SIZE);   

    // memory map the shared memory object
    *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);     

    sprintf(*ptr, "%s", content);
}



int main(int argc, char* argv[])
{
    // Flags for 'getopt'
    int flag_r = -1;
    int flag_s = -1;
    char* flag_name = NULL;
    
    // Only continue when all flags are pared correctly
    if (!evaluateAndStoreFunctionArguments(argc, argv, &flag_r, &flag_s, &flag_name)) return -1;
    
    // size of shared memory will be equal to all the letters in the alphabet
    const int SIZE = flag_s;
    // name of shared memory object
    char* name = flag_name;
    char* content = "abcdefghijklmnopqrstuvwxyz";
    // shared memory file descriptor
    int shm_fd; 
    // Universal pointer, that can take any type
    void* ptr;

    // pointer to shared memory obect
    createSharedMemoryObject(shm_fd, &ptr, name, SIZE, content);

    // Tracking variable of total number of runs that the program should execute
    int numberOfRuns = 0;

    while (numberOfRuns < flag_r)
    {
        // If first character (lower case 'a') has changed to upper case A, delete shared memory
        if ((*(char*)ptr) == 'A')
        {
            // If the program should repeat more times, accordinly to -r argument, create shared memory again and wait for upper case 'A'.
            if (numberOfRuns < flag_r)
            {
                // Create new shared memory
                createSharedMemoryObject(shm_fd, &ptr, name, SIZE, content);

                printf("Run: %d\n", ++numberOfRuns);
            }
        }
    }
    // Delete shared memory
    shm_unlink(name);

    return 0; 
}
