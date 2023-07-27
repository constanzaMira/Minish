#include "builtin.h"

/*
Attempts to execute an external command via fork/execvp.
The return value is the status of the executed external command.
*/

int externo(__attribute__((unused))int argc, char **argv)
{
    struct sigaction old_str_sigint_action, new_str_sigint_action;
    int status;
    pid_t pid = fork();

    if (pid < 0){
        perror("fork faild\n");
        return EXIT_FAILURE;
    } else if (pid == 0){
        execvp(argv[0], argv);
        error(0,errno,"execvp error\n");
        exit(EXIT_FAILURE);
    } else{
        memset(&new_str_sigint_action, 0, sizeof(new_str_sigint_action)); // fill with 0's the struct
        new_str_sigint_action.sa_handler = SIG_IGN; // handler is a func o SIG_DFL o SIG_IGN
        sigaction(SIGINT, &new_str_sigint_action, &old_str_sigint_action); // execute sigaction, activate handler

        pid_t childpid = waitpid(pid, &status, 0);
        sigaction(SIGINT, &old_str_sigint_action, NULL);
        if(childpid < 0){
            perror("waitpid error\n");
            return EXIT_FAILURE;
        } else if(childpid == 0){
            perror("waitpid returned 0\n");
            return EXIT_FAILURE;
        } else{
            if(WIFEXITED(status)){
                status = WEXITSTATUS(status);
            } else{
                perror("child process did not terminate with exit\n");
                return EXIT_FAILURE;
            }
        }
        
        return status;
    }
}
