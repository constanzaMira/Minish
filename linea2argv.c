#include "builtin.h"

/*
Converts a line of text (terminated with '\n') into an argument vector (argv).
- The function points argv[0] to the first word, argv[1] to the second word, and so on.
- argc+1 is the size of argv as defined in the caller of this function.
- Returns the number N of words found, and argv[N] should be set to NULL. It is assumed that N is less than argc. Any extra words can be discarded.
- A word is a text delimited by spaces or tabs.
- The purpose of this function is to construct argv for invoking the previous functions.
- It should work perfectly even if the line is empty or contains only spaces. In such cases, it returns 0.
- The strings pointed to by argv[0], argv[1], etc., will be dynamically allocated. It is the responsibility of the caller of linea2argv to free them appropriately.
Returns 0 on success, 1 on error.
*/

int linea2argv (char *linea, int argc, char **argv);

int linea2argv (char *linea, int argc, char **argv)
{
    int count = 0;
    char *line_aux = strdup_or_exit(linea);
    char *word = strtok(line_aux, " \t\n");

    for(int i=0; word != NULL && i<argc; i++){
        argv[i] = strdup_or_exit(word);
        count++;
        word = strtok(NULL, " \t\n");
    }

    argv[count] = NULL;
    free(line_aux);
    return count;
}
