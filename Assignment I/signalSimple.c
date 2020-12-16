#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <getopt.h>

static void installHandler(int);
static void callProcess(pid_t, int);
static int evaluateAndStoreFunctionArguments (int, char**, int*, int*);

static char * 	progname;
static bool		to_quit = false;
static int		delaySeconds = 3;
static int 		state = 0;
union sigval sigValues;

// Check all passed arguments that user passed to function when executing
static int evaluateAndStoreFunctionArguments (int argc, char** argv, int* process_id, int* process_signal)
{
    int opt = 0;
    // when 'getopt' does not return -1, continue
    while ((opt = getopt(argc, argv, "hs:")) != -1) 
    {
        // Evaluate individual flags
        switch(opt) 
        {
            case 'h':
                printf("\nEmbedded linux, assignment I. \n\n optional flag is: -s {\"PROCESS ID\" + \"SIGNAL ID\"}\n\n");
                return -1;
                break;    
            case 's':
                *process_id = atoi(argv[2]);
				*process_signal = atoi(argv[3]);
				return 0;
                break;       
                // Check other options
            case '?':              
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                abort();
            default:
				break;                
        }
    }
	return 1;
}


static void my_sig_handler (int signum, struct act)
{
	printf ("\n%s: signal %d received\n", progname, signum);
}

static void installHandler (int sig)
{
	if (signal(sig, my_sig_handler) != SIG_ERR) printf("Sucessfully created handler");
	
}

static void callProcess(pid_t target_pid, int sig)
{
	struct sigaction action;
	action.sa_handler = my_sig_handler;
	action.sa_flags = SA_SIGIN;

	sigaction(sig, &sigValues, NULL);
}

int main(int argc, char * argv[])
{
    int     sig;
	char 	choice;
    int     target_pid;
	int		i = 0;
    
	int state = evaluateAndStoreFunctionArguments(argc, argv, &target_pid, &sig);

    // Quit program if error occurs in parameters
    if (state == -1) return -1;
	// If user did not enter parameters, give option menu
	else if (state == 0) 
	{
		// Sent signal
		callProcess(target_pid, sig);
		// Quit
		return -1;
	}

    progname = argv[0];

	while (choice != 'q')
    {
        printf ("\n%d: Enter choice (i, s, t ,h ,q): ", getpid());
        scanf("%s", &choice);
        printf ("\n");
        
        switch (choice)
        {
            case 'i':
				printf("\nInstall new handler\n");
				printf("\nEnter the signal number: \n");
				scanf("%d", &sig);
				installHandler(sig);
                break;
            case 's':
                printf ("\nSend a signal\n");
				printf("\nEnter the process number: \n");
				scanf("%d", &target_pid);
				printf("\nEnter the signal number: \n");
				scanf("%d", &sig);
				callProcess(target_pid, sig);
                break;
            case 't':
				printf("\nSet a timer\n");

                break;
            case 'q':
                break;
            case 'h':
            case '?':
                printf ("Options:\n"
                        "========\n"
                        "    [n]  create new shm\n"
                        "    [o]  open existing shm\n"
                        "    [w]  write\n"
                        "    [r]  read\n"
                        "    [c]  close\n"
                        "    [u]  unlink\n"
                        "    [h]  help\n"
                        "    [q]  quit\n");
                break;
            default:
                printf ("Invalid option '%c' (%#x)\n", choice, choice);
                break;
        }
    }
}

