#include "builtin.h"

/*
cd [dir] - Change the current directory. It accepts one parameter. Additionally, it sets
the environment variable PWD to the absolute pathname of the current directory. The parameter can have the following values:
    -->cd xxx (changes to xxx directory)
    -->cd – (changes to the previous directory – serves to make cd to another directory and power
            "back" quickly)
    --> cd (changes to directory value of HOME environment variable)
returns 0 on success, 1 on error
*/

int builtin_cd(int argc, char **argv)
{
    char *home_dir = getenv("HOME"); //get home directory
    char *old_dir = getenv("OLDPWD"); //get old directory
    char *current_dir = getcwd(NULL, 0); //get current directory

    if(current_dir == NULL){ //check for errors
        free(current_dir);
        perror("error trying to get current or old directory");
        return EXIT_FAILURE;
    }
    
    if(argc > 2){
        free(current_dir);
        perror("cd: too many arguments");
        return EXIT_FAILURE;
    }
    
    if(argc == 1) { //default (cd) move to home directory
        if (chdir(home_dir) == -1){
            free(current_dir);
            perror("error trying to change to home directory");
            return EXIT_FAILURE;
        }
        if (setenv("OLDPWD", current_dir, 1) == -1){
            free(current_dir);
            perror("error trying to set old directory");
            return EXIT_FAILURE;
        }
    } else { //recieves cd xxx or cd -
        if(strcmp(argv[1], "-") == 0){
            if(chdir(old_dir) == -1){ //move back and check for errors
                free(current_dir);
                perror("error trying to move back");
                return EXIT_FAILURE;
            }
            if(setenv("OLDPWD", current_dir, 1) == -1){ // set new path and check for errors
                free(current_dir);
                perror("error trying to set old directory");
                return EXIT_FAILURE;
            }
        } else {
            if(chdir(argv[1]) == -1){ //move foward and check for errors
                free(current_dir);
                perror("error trying to change directory");
                return EXIT_FAILURE;
            }
            if(setenv("OLDPWD", current_dir, 1) == -1){ // set new path and check for errors
                free(current_dir);
                perror("error trying to set old directory");
                return EXIT_FAILURE;
            }
        }
    }
    
    free(current_dir);
    return EXIT_SUCCESS;
}
