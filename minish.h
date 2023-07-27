#define MAXLINE 1024        // tamaño máximo de la línea de entrada
#define MAXCWD 1024         // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256        // cantidad máxima de palabras en la línea
#define MAX_GROUPS 32       // cantidad máxima de grupos a los que pertenece un usuario
#define HISTORY_FILE	".minish_history"   // nombre del archivo que almacena historia de comandos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <libgen.h>
#include "wrappers.h"

extern int globalstatret;	// save last command status
extern struct deq *history;
extern char *current_dir;
extern char **environ;


/*
    builtin_arr is a list of the built-ins, which will be traversed linearly. 
    While a data structure that improves search speed could be used, for this exercise, 
    a linearly traversed list is sufficient. It should be defined and initialized as a 
    global variable in the main program as follows:

    struct builtin_struct builtin_arr[] = {
        { "cd", builtin_cd, HELP_CD },
        .... etc. etc
        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };

    The definition cannot be placed in the minish.h file because it is intended to be included in all source files, 
    and defining the same array in different source files of the same program is not allowed.
*/

extern int ejecutar (int argc, char ** argv);
extern int externo (int argc, char ** argv);
extern int linea2argv(char *linea, int argc, char **argv);
