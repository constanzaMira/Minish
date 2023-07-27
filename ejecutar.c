#include "builtin.h"

/*
Decide if it is a built-in command, if it is, executes it.
Otherwise, invokes externo(). The return value is the status
of the executed command.
*/

int ejecutar(int argc, char **argv)
{
    if(argc == 0){
        return EXIT_SUCCESS;
    }
    
    struct builtin_struct *cmd = builtin_lookup(argv[0]);
    if(cmd != NULL){
        return cmd->func(argc, argv);
    }

    return externo(argc, argv);
}
