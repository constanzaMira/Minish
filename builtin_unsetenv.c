#include "builtin.h"

/*
unsetenv var [var...] - removes environment variables.
Returns 0 on success, 1 on error.
*/

int builtin_unsetenv(int argc, char **argv)
{
    if(argc > 1){
        for (int i=0; i<argc; i++){ //for each argument(variable)
            int env = unsetenv(argv[i]); //get environment variable value

            if (env == -1){ //check for errors
                perror("error trying to unset environment variable");
                return EXIT_FAILURE;
            }

            printf("%s unset\n", argv[i]);
        }
    }else{
        printf("no arguments given\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
