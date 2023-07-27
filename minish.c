#include "minish.h"
#include "builtin.h"
#include "deq.h"

int globalstatret;
struct deq *history;

void write_prompt_string();
void sigint_handler();
void append_to_history(char* );
void save_command_history_to_file(const char*);
void exit_handler(char *);

struct builtin_struct builtin_arr[] = 
{
    {"exit", builtin_exit, HELP_EXIT},
    {"pid", builtin_pid, HELP_PID},
    {"gid", builtin_gid, HELP_GID},
    {"uid", builtin_uid, HELP_UID},
    {"getenv", builtin_getenv, HELP_GETENV},
    {"setenv", builtin_setenv, HELP_SETENV},
    {"unsetenv", builtin_unsetenv, HELP_UNSETENV},
    {"cd", builtin_cd, HELP_CD},
    {"status", builtin_status, HELP_STATUS},
    {"help", builtin_help, HELP_HELP},
    {"dir", builtin_dir, HELP_DIR},
    {"history", builtin_history, HELP_HISTORY},
    {"copiar", builtin_copiar, HELP_COPIAR},
    {NULL, NULL, NULL}
};

int main()
{
    char *current_dir = getcwd(NULL, 0); //get current directory
    setenv("OLDPWD", current_dir, 1); //set old directory as current when it starts
    free(current_dir);

    struct sigaction str_sigint_action;
    char line[MAXLINE];
    char *argv[MAXLINE];
    int argc;

    memset(&str_sigint_action, 0, sizeof(str_sigint_action)); // fill with 0's the struct
    str_sigint_action.sa_handler = sigint_handler; // handler is a func o SIG_DFL o SIG_IGN
    sigaction(SIGINT, &str_sigint_action, NULL); // execute sigaction, activate handler

    char *home_dir = getenv("HOME");
    const char *minish_dir = "/.minish_history";

    size_t total_size = strlen(home_dir) + strlen(minish_dir) + 1;
    char *filename = (char*) malloc(total_size);

    if(filename == NULL){
        perror("error trying to asign memory\n");
        return EXIT_FAILURE;
    }

    strcpy(filename, home_dir); //copy home dir to keep original one
    strcat(filename, minish_dir); //concatenate home dir with minish dir

    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        char line[MAXLINE];
        while (fgets(line, MAXLINE, file) != NULL) {
            append_to_history(line);
        }

        fclose(file);
    }

    while (1)
    {
        write_prompt_string();
        clearerr(stdin);

        if(fgets(line, MAXLINE, stdin) != NULL){
            if(strspn(line, " \t\n\r") == strlen(line)) continue;  //check for empty line
            argc = linea2argv(line, MAXLINE, argv);
            if(argc > 0) {
                append_to_history(line);
                if(strcmp(argv[0], "exit") == 0){
                    exit_handler(filename);
                    break;
                }

                globalstatret = ejecutar(argc, argv);

                // Free each argv[i] after executing the command
                for(int i = 0; i < argc; i++){
                    free(argv[i]);
                }
            }
        }else{
            if(feof(stdin)){
                break;
            }
        }
    }

    save_command_history_to_file(filename); //append history in file
    free(filename);
    return EXIT_SUCCESS;
}

void write_prompt_string()
{
    char *dir = getcwd(NULL, 0); //get current directory
    struct passwd *pw = getpwuid(getuid());

    if(pw == NULL){ //get username
        free(dir);
        perror("error trying to get username");
        exit(EXIT_FAILURE);
    }

    if(dir == NULL){ //get current working directory
        free(dir);
        perror("error trying to get current working directory");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "(minish) %s:%s ", pw->pw_name, dir); //print prompt
    free(dir);
}

void sigint_handler ()
{
    fprintf(stderr, "Interrupt\n");
}

void append_to_history(char* line)
{
    if (history==NULL){
        history=deq_create();
    }

    deq_append(history,line);
}

void save_command_history_to_file(const char* filename)
{
    FILE* history_file = fopen(filename, "w");
    if (history_file == NULL) {
        perror("error opening file");
        return;
    }

    struct deq_elem* current = history->leftmost;
    while (current != NULL) {
        fprintf(history_file, "%s", current->str);
        current = current->next;
    }

    deq_free_memory(history);
    fclose(history_file);
}

void exit_handler(char *filename)
{
    save_command_history_to_file(filename);
    exit(EXIT_SUCCESS);
}
