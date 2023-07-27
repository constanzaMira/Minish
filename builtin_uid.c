#include "builtin.h"

/*
uid - It takes no parameters and displays the user ID as a number and also the username.
Returns 0 on success, 1 on error.
*/

int builtin_uid(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
    uid_t uid = getuid(); //get user id
    struct passwd *pw = getpwuid(uid); //get user name from user id

    if(pw == NULL || (int) uid == -1){ //check for errors
        perror("error trying to get user id or username");
        return EXIT_FAILURE;
    }

    printf("Uid: %d, Name: %s, Info: %s\n", uid, pw->pw_name, pw->pw_gecos); //print user id, username and user info
    return EXIT_SUCCESS;
}
