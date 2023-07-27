#include "builtin.h"

/*
help [command] accepts up to one parameter, which is the command for which a
more extensive help will be displayed. Without any arguments, it writes a help text indicating the
available internal commands. Returns 0 on success, 1 on error.
*/

int builtin_help(int argc, char **argv)
{
    if(argc == 2){
        for (int i = 0; builtin_arr[i].cmd != NULL; i++){
            if(strcmp(argv[1],builtin_arr[i].cmd) == 0){
                printf("%s - %s\n", builtin_arr[i].cmd, builtin_arr[i].help_txt);
                return EXIT_SUCCESS;
            }
        }
        printf("command not found\n");
        return EXIT_FAILURE;
    }else if(argc == 1){
        for (int i = 0; builtin_arr[i].cmd != NULL; i++){
            printf("%s - %s\n", builtin_arr[i].cmd, builtin_arr[i].help_txt);
        }
    }else{
        printf("wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
