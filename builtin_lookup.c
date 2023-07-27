#include "builtin.h"

/*
struct builtin_struct * builtin_lookup(char *cmd);
--> Checks if cmd is indeed a built-in command. If it is, it returns a
pointer to that structure. If not, it returns NULL.
*/

struct builtin_struct *builtin_lookup(char *cmd)
{
    for (int i = 0; builtin_arr[i].cmd != NULL; i++){
        if(strcmp(cmd, builtin_arr[i].cmd) == 0){
            return &builtin_arr[i];
        }
    }
    return NULL;
}
