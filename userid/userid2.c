#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

int main(void)
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
    printf(" groups=%d(%s),", getgid(), getgrgid(getgid())->gr_name);

    while(grg != NULL)
    {
        //printf("baza: %d\n", grg);
        for(int i = 0; grg->gr_mem[i] != NULL; i++)
        {
            if(strcmp(uname, grg->gr_mem[i]) == 0) 
                printf(" %d(%s),\n", grg->gr_gid, grg->gr_name); 
            //grg->gr_mem++;
            //printf("cringe: %d\n", i);
        }
        grg = getgrent();
    }

    return 0;
}

