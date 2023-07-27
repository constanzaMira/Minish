#include "minish.h"

struct builtin_struct {         // struct with information of builtins
    char *cmd;                  // name of builtin command
    int (*func) (int, char **); // pointer to function that implements the builtin
    char *help_txt;             // help text
};

extern struct builtin_struct builtin_arr[];

#define HELP_CD  "cd [..|dir] - changes the current directory"
#define HELP_DIR "dir [str] - 5 usages:\n"\
                    "\t1. If only 'dir' is indicated, it displays the files in the current directory with their respective additional data.\n"\
                    "\t2. 'dir -l' will only show the files in the current directory without extra information.\n"\
                    "\t3. 'dir directory text' displays all the files in the entered directory whose name contains that text.\n"\
                    "\t4. 'dir text' displays all the files in the current directory where the entered text is included in the name.\n"\
                    "\t5. 'dir directory' displays all the files in the entered directory.\n"
#define HELP_EXIT "exit [status] - terminates minish with a return status (default 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid|unsetenv|gid]"
#define HELP_HISTORY "history [N] - by default, displays the last N (10) written commands"
#define HELP_GETENV  "getenv var [var] - displays the value of environment variable(s)"
#define HELP_PID     "pid - displays the Process Id of the minish"
#define HELP_SETENV  "setenv var value - adds or changes the value of an environment variable"
#define HELP_UNSETENV "unsetenv var [var...] - removes the specified environment variable(s)"
#define HELP_STATUS  "status - displays the return status of the last executed command"
#define HELP_UID     "uid - displays the username and user ID of the owner of the minish"
#define HELP_GID    "gid - displays the primary group and secondary groups of the user"
#define HELP_COPIAR "copiar - 2 usages:\n"\
                        "\t1.[file1] [file2] - copies the contents of file1 to file2 or creates file2 if it does not exist.\n"\
                        "\t2.[file1...] [dir] - copies the contents of file1 and others to the directory dir"

extern struct builtin_struct * builtin_lookup(char *cmd);
extern int builtin_exit (int argc, char ** argv);
extern int builtin_help (int argc, char ** argv);
extern int builtin_history (int argc, char ** argv);
extern int builtin_status (int argc, char ** argv);
extern int builtin_cd (int argc, char ** argv);
extern int builtin_dir (int argc, char ** argv);
extern int builtin_getenv (int argc, char ** argv);
extern int builtin_gid (int argc, char ** argv);
extern int builtin_setenv (int argc, char ** argv);
extern int builtin_pid (int argc, char ** argv);
extern int builtin_uid (int argc, char ** argv);
extern int builtin_unsetenv (int argc, char ** argv);
extern int builtin_copiar (int argc, char ** argv);
