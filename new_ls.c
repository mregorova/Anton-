#include <stdio.h>
#include <sys/stat.h>
#include <getopt.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

void ls(char* path, int flag_a, int flag_R, int flag_l)
{
    DIR* d = opendir(".");
    struct dirent* dnt;
    struct stat filestat;
    

    while((dnt = readdir(d)) != NULL) {

        char new_path[512];
        snprintf(new_path, 512, "%s/%s", path, dnt->d_name);
        stat(new_path, &filestat);

        if (flag_l == 1)
        {
            struct passwd* user = getpwuid(filestat.st_uid);
            struct group* group = getgrgid(filestat.st_gid);

            printf("%-4hu", filestat.st_nlink);
            printf("%-20s", user->pw_name);
            printf("%-8s", group->gr_name);
            printf("%-6lld", filestat.st_size);
            printf(" ");
        }

        printf("%s", dnt->d_name);

        if (S_ISDIR(filestat.st_mode) == 1) printf("/");

        printf("\n");
    }
    closedir(d);

    if (flag_R == 0) 
    {
        return;
    }
    printf("\n");
    
    d = opendir(path);
    while((dnt = readdir(d)) != NULL)
    {

        char new_path[512];
        snprintf(new_path, 512, "%s/%s", path, dnt->d_name);
        stat(new_path, &filestat);

        if (S_ISDIR(filestat.st_mode) == 1)
        {
            char new_path[512];
            snprintf(new_path, 512, "%s/%s", path, dnt->d_name);
            printf("%s:\n", new_path);
            ls(new_path, flag_a, flag_R, flag_l);
        }
    }
    closedir(d);
}
    

int main(int argc, char** argv) {

    const struct option long_option[] =
    {
        {"all", no_argument, NULL, 'a'},
        {"long", no_argument, NULL, 'l'}, 
        {"recursive", no_argument, NULL, 'R'},
        {NULL, no_argument, NULL, 0}
    };
	int long_index;
    int opt;
    const char short_option[] = "alR";
    
    int flag_a = 0, flag_l = 0, flag_R = 0;

    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'R': flag_R = 1;
            break;
        case 'a': flag_a = 1;
            break;
        case 'l': flag_l = 1;
            break;
        case '?': printf("Unknown parameter: -%c\n", optopt);
        }
    }

    ls(argv[optind] == NULL ? "." : argv[optind], flag_a, flag_R, flag_l);

    return 0;
}