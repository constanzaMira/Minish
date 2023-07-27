#include "builtin.h"

/*
pid - It takes no parameters and displays the process ID of the shell.
Returns 0 on success, 1 on error.
*/

int builtin_pid(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
    pid_t pid = getpid(); //get process id
    pid_t ppid = getppid(); //get father process id, no error return
    
    if (pid == -1){ //check for errors
        perror("error trying to get process id");
        return EXIT_FAILURE;
    }

    printf("pid: %d, ppid: %d\n", pid, ppid);
    return EXIT_SUCCESS; //return process id
}
