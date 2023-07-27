#include "builtin.h"
#include <sys/types.h>

/*
dir [text/directory] – Simulates simplified execution of the ls -l command. Without
arguments, it displays the list of files in the current directory. With a single argument,
it can be either a text or a directory:
--> If it corresponds to an existing directory, it shows the list of all files in that directory.
--> If it is not a directory, it displays all files whose names contain that text.
With two arguments, it combines the functionality of the previous cases: the first
argument must be a directory (otherwise, it is an error), and the second argument is the filter text.
-> dir -l is an adittional option that displays the list of files in the current directory but printing
the information in a more orderly way. Returns 0 on success, 1 on error.
*/ 

int compare_names(const void *a, const void *b);
void print_dir_l(DIR *dir);
void print_dir(DIR *dir);
void print_dir_filter_by_text(DIR *dir, char *word);
void print_information(const char *file_name, DIR *dir);

int builtin_dir(int argc, char **argv)
{
    DIR *dir;
    dir = opendir(".");

    if(dir == NULL){ //check for errors
        perror("error trying to get directory");
        return EXIT_FAILURE;
    }

    if(argc > 3){
        fprintf(stderr, "dir: too many arguments\n");
        closedir(dir);
        return EXIT_FAILURE;
    }else if(argc == 3){ //recieves dir and text
        DIR *new_dir = opendir(argv[1]);
        if(new_dir == NULL){ // checks if exists dir
            fprintf(stderr, "dir %s: No such file or directory\n", argv[1]);
            return EXIT_FAILURE;
        }

        print_dir_filter_by_text(new_dir, argv[2]);
        closedir(new_dir);
    }else if (argc == 2){ //recieves just dir or text
        if(strcmp(argv[1], "-l") == 0){ //recieves -l
            print_dir_l(dir);
        } else {
            DIR *new_dir = opendir(argv[1]);
            if(new_dir == NULL){ // checks if it's a dir or text
                //is text

                print_dir_filter_by_text(dir, argv[1]);
            }else{
                //is a directory

                print_dir(new_dir);
                closedir(new_dir);
            }
        }
    }else{
        print_dir(dir);
    }

    closedir(dir);
    return EXIT_SUCCESS; 
}

void print_dir_l(DIR *dir)
{
    int file_count;
    struct dirent *dirent;
    while((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) { // ignore "." and ".." entry
            printf("%-30s", dirent->d_name);
            file_count++;
            if (file_count % 4 == 0) { //
                printf("\n");
            }
        }
    }

    if (file_count % 4 != 0) { // if the last line is not complete, print a new line at the end
        printf("\n");
    }
}

void print_dir(DIR *dir)
{
    int file_count = 0;
    struct dirent *dirent;
    char *files_names[MAXLINE];
    while((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) { // ignore "." and ".." entry
            files_names[file_count] = strdup_or_exit(dirent->d_name);
            file_count++;
        }
    }

    qsort(files_names, file_count, sizeof(char *), compare_names);

    for(int i=0; i<file_count; i++){
        print_information(files_names[i], dir);
        free(files_names[i]);
    }
}

void print_dir_filter_by_text(DIR *dir, char *word)
{
    int file_count = 0;
    struct dirent *dirent;
    char *files_names[MAXLINE];
    while((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) { // ignore "." and ".." entry
            char *name = dirent->d_name;
            if(strstr(name, word) != NULL){ //compare directory name with text
                files_names[file_count] = strdup_or_exit(dirent->d_name);
                file_count++;
            }
        }
    }
    qsort(files_names, file_count, sizeof(char *), compare_names);

    for(int i=0; i<file_count; i++){
        print_information(files_names[i], dir);
        free(files_names[i]);
    }
}

void print_information(const char *file_name, DIR *dir)
{
    struct stat st;
    if (fstatat(dirfd(dir), file_name,&st, 0) == -1) {
        perror("stat");
        return;
    }

    // permissions
    printf((S_ISDIR(st.st_mode)) ? "d" : "-");
    printf((st.st_mode & S_IRUSR) ? "r" : "-");
    printf((st.st_mode & S_IWUSR) ? "w" : "-");
    printf((st.st_mode & S_IXUSR) ? "x" : "-");
    printf((st.st_mode & S_IRGRP) ? "r" : "-");
    printf((st.st_mode & S_IWGRP) ? "w" : "-");
    printf((st.st_mode & S_IXGRP) ? "x" : "-");
    printf((st.st_mode & S_IROTH) ? "r" : "-");
    printf((st.st_mode & S_IWOTH) ? "w" : "-");
    printf((st.st_mode & S_IXOTH) ? "x" : "-");

    // number of links
    printf("%2ld ", st.st_nlink);

    // owner and group
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    printf("%-8s ", (pw) ? pw->pw_name : "");
    printf("%-8s ", (gr) ? gr->gr_name : "");

    // size of file
    printf("%8ld ", st.st_size);

    // modification date
    struct tm *tm = localtime(&st.st_mtime);
    char date_string[80];
    strftime(date_string, sizeof(date_string), "%b %d %H:%M", tm);
    printf(" %s", date_string);

    // file name
    printf(" %s\n", file_name);
}


int compare_names(const void *a, const void *b) // comparison func for qsort
{
    const char *nombre1 = *(const char **)a;
    const char *nombre2 = *(const char **)b;
    return strcmp(nombre1, nombre2);
}