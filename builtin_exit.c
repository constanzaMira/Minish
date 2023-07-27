#include "builtin.h"

/*
exit_minish: Terminates the shell, optionally accepting a parameter that represents the exit status. If no parameter
is provided, it uses the exit status of the last executed command.
Returns 0 on success, 1 on error.
*/

int builtin_exit(int argc, char **argv)
{
    int status;
    if (argc==1){
        exit(globalstatret); //return last command status
        return globalstatret;
    }
    else if (argc==2){ //assume second argument is status return
        status= atoi(argv[1]);
        if(status==0){
            error(0, 0, "parameter must be an integer");
            return EXIT_FAILURE;
        }else{
            exit(status);
            return status;
        }
    }
    else{
        error(0, 0, "too many arguments");
        return EXIT_FAILURE;
    }
}
