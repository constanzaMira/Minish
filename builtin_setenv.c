#include "builtin.h"

/*
setenv variable value - defines a new environment variable or changes the value of
a existing environment variable. Returns 0 on success, 1 on error.
*/

int builtin_setenv(int argc, char **argv)
{
    if(argc == 3){
        char *env = getenv(argv[1]); //get environment variable value
        int new_env;

        if (env == NULL){ //check if variable exists
            new_env = setenv(argv[1], argv[2], 0);
        }

        int overw_env = setenv(argv[1], argv[2], 1);

        if(new_env == -1 || overw_env == -1){ //check for errors
            perror("error trying to set environment variable");
            return EXIT_FAILURE;
        }
    } else {
        printf("wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

