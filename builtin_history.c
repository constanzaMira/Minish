#include "builtin.h"
#include "deq.h"

/*
history [N] (displays the previous N commands, default is 10, that should be stored
for future executions of minish, in the file $HOME/.minish_history). The handling of
history should be done in memory, using a data structure that needs to be selected
and documented. The "past" history is read from the file "$HOME/.minish_history" upon
starting the shell, and the new session's content is dumped to the file upon exiting the
shell. It is recommended to discuss the design of this functionality with the instructor
before implementing it. Any other command will attempt to execute as an external command.

We have decided to use a double-ended queue (deque) implemented with a doubly linked list
to store the commands that are executed. Returns 0 on success, 1 on error.
*/

int builtin_history (int argc, char **argv)
{
    if(argc > 2){
        printf("history: too many arguments\n");
        return EXIT_FAILURE;
    }

    if(argc == 1){
        deq_print_left(history, 10);
    }else{
        char *endptr;
        long int quantity = strtol(argv[1], &endptr, 10);

        if(argv[1] == endptr){
            printf("history: wrong argument %s - help history\n", argv[1]);
            return EXIT_FAILURE;  
        }

        deq_print_left(history, (int) quantity);
    }

    return EXIT_SUCCESS;
}
