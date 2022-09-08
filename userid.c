#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

int main()
{
    struct passwd *getpwuid(uid_t uid);
    struct group *getgrgid(gid_t gid);
    struct group *grg = getgrent();

    char* uname;
    char* gname;
    uname = getpwuid(getuid()) -> pw_name;
    gname = getgrgid(getgid()) -> gr_name;

    printf("uid=%d", getuid());
    printf("(%s)", uname);
    printf(" gid=%d", getgid());
    printf("(%s)", gname);

    while(grg != NULL)
    {
        while(*grg->gr_mem != NULL)
        {
            if(strcmp(uname, *grg->gr_mem) == 0) 
                printf("%d(%s)", grg->gr_gid, grg->gr_name); 
            grg->gr_mem++;
        }
        getgrent();
    }

    return 0;
}

