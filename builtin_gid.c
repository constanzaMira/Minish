#include "builtin.h"

/*
gid: Takes no parameters and displays the primary group and secondary
groups of the user. Returns 0 on success, 1 on error.
*/

int builtin_gid(__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
    gid_t primaryGid = getgid();
    gid_t groupIDs[MAX_GROUPS];
    int numGroups = getgroups(MAX_GROUPS, groupIDs);

    struct group *primaryGr = getgrgid(primaryGid);
    
    if ((int) primaryGid == -1 || numGroups == -1){ //check for errors
        perror("error trying to get principal group id or secondary group ids");
        return EXIT_FAILURE;
    }

    printf("Real Gid: %d (%s) \n", primaryGid, primaryGr->gr_name); //print principal group id
    printf("Groups: ");
    for(int i=0; i<numGroups; i++){
        struct group *gr = getgrgid(groupIDs[i]);

        if (gr == NULL){ //check for errors
            perror("error trying to get group name");
            return EXIT_FAILURE;
        }

        if(i == numGroups-1) printf("%d (%s)\n", gr->gr_gid, gr->gr_name); //print last secondary group id and name
        else printf("%d (%s), ", gr->gr_gid, gr->gr_name); //print secondary group ids and names
    }
    
    return EXIT_SUCCESS;
}
