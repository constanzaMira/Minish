#include "builtin.h"

/*
getenv variable [variable ...]: Displays the values of the specified environment variables.
The parameters are the environment variables for which you want to know the value.
The output consists of a series of lines in the format variable=value.
If no parameters are provided, it displays all environment variables.
Returns 0 on success, 1 on error.
*/

int builtin_getenv(int argc, char **argv)
{
    if(argc > 1){
        for (int i=1; i<argc; i++){ //for each argument(variable)
            char *env = getenv(argv[i]); //get environment variable value

            if (env == NULL){ //check for errors
                perror("error trying to get environment variable");
                return EXIT_FAILURE;
            }

            printf("%s=%s\n", argv[i], env); //print variable=value
        }
    }else{
        char **env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }  
    }

    return EXIT_SUCCESS;
}
