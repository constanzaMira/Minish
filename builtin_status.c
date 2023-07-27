#include "builtin.h"

/*
status - It takes no parameters and displays the return status
of the last executed command. Typically, it would be 0 for a
successful command and a different value if there were errors.
It should work correctly for both external command execution
(capturing the status in the waitpid system call) and builtin
command execution. Returns 0 on success, 1 on error.
*/

int builtin_status(int argc, __attribute__((unused))char **argv)
{
    if(argc != 1){
        fprintf(stderr, "status: too many arguments\n");
        return EXIT_FAILURE;
    }
    printf("status: %d\n", globalstatret);
    return EXIT_SUCCESS;
}
