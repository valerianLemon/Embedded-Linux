#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

int
main (void)
{
    pid_t processID;      /* Process ID from fork() */
    static int  shm_fd = -1;
    int rtnval;
    int shm_size = 2;
    char *shm_addr;
    char *shm_name = "fork_temp";
    char flag0 = '0';
    char flag1 = '1';
    
    shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }

    rtnval = ftruncate (shm_fd, shm_size);
    if (rtnval != 0)
    {
        perror ("ERROR: ftruncate() failed");
    }

    shm_addr = (char *) mmap (NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }
    memcpy(shm_addr, &flag1, 1);

    /* creating the threads */
    processID = fork();
    if (processID < 0)
    {
        // fatal error!
        perror("fork() failed");
    }
    else
    {
        if (processID == 0)
        {   
            while ((*(char*)shm_addr) == '0'){}

            printf ("%d: 2\n", getpid());
            sleep(2);

            memcpy(shm_addr, &flag0, 1);
            while ((*(char*)shm_addr) == '0'){}

            printf ("%d: 4\n", getpid());
            sleep(2);

            memcpy(shm_addr, &flag0, 1);
            while ((*(char*)shm_addr) == '0'){}

            printf ("%d: 6\n", getpid());
            sleep(2);
            
            /* Child process terminates */
            exit(1);
        }
        else
        {
            //Print first vlaue
            printf ("%d: 1\n", getpid());
            sleep(2);

            //set the flag and wait for it
            memcpy(shm_addr, &flag1, 1);

            while ((*(char*)shm_addr) == '1'){}

            printf ("%d: 3\n", getpid());
            sleep(2);

            //set the flag and wait for it
            memcpy(shm_addr, &flag1, 1);
            while ((*(char*)shm_addr) == '1'){}

            printf ("%d: 5\n", getpid());
            sleep(2);

            //set the flag and wait for it
            memcpy(shm_addr, &flag1, 1);
        }
    }
    shm_unlink(shm_name);
    return (0);
}
