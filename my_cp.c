#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <utime.h>
#include <unistd.h>


void cp(char* path1, char* path2, int flag_v, int flag_i, int flag_f, int flag_p)
{
    FILE* file1 = fopen(path1, "r");

    if (file1 == NULL)
    {
        printf("An error occured with file1\n");
        return;
    }

    if (access(path2, F_OK) != -1 && flag_i == 1)
    {
        printf("Overwrite %s? (y/n [n])\n", path2);
        int answer = getc(stdin);
        if (answer != 'y')
        {
            printf("Not overwritten\n");
            fclose(file1);
            return;
        }
    }

    FILE* file2 = fopen(path2, "w");

    if (file2 == NULL && errno == EACCES && flag_f == 1)
    {
        remove(path2);
        file2 = fopen(path2, "w");
    }

    if (file2 == NULL)
    {
        printf("An error occured with file2\n");
        fclose(file1);
        return;
    }

    char symb;
    while (fread(&symb, 1, 1, file1))
    {
        fwrite(&symb, 1, 1, file2);
    }

    if (flag_v == 1)
    {
        printf("\"%s\" > \"%s\"\n", path1, path2);
    }

    if (flag_p == 1)
    {
        struct stat filestat;
        stat(path1, &filestat);
        chmod(path2, filestat.st_mode);
        chown(path2, filestat.st_uid, filestat.st_gid);
        struct utimbuf Time;
        time_t mtime;
        mtime = filestat.st_mtime;
        Time.actime = filestat.st_atime;
        utime(path2, &Time);
    }

    fclose(file1);
    fclose(file2);
}

int main(int argc, char** argv)
{
    const struct option long_option[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"interactive", no_argument, NULL, 'i'},
        {"force", no_argument, NULL, 'f'},
        {"preserve", no_argument, NULL, 'p'},
        {NULL, no_argument, NULL, 0}
    };

    int long_index;
    const char short_option[] = "hvifp";
    int opt;
    int flag_h = 0, flag_v = 0, flag_i = 0, flag_f = 0, flag_p = 0;

    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'h': flag_h = 1;
            break;
        case 'v': flag_v = 1;
            break;
        case 'i': flag_i = 1;
            break;
        case 'f': flag_f = 1;
            break;
        case 'p': flag_p = 1;
            break;
        case '?': printf("Unknown parameter: -%c\n", optopt);
        }
    }

    if (flag_h == 1)
    {
        printf("\nNAME\n");
        printf("\tcp -- copy files\n");
        printf("\nSYNOPSIS\n");
        printf("\tcp [-h | -v | -i | -f | -p] source_file target_file\n");
        printf("\nDESCRIPTION\n");
        printf("\tFlags:\n\n");
        printf("\t -h\t help\n");
        printf("\t -v\t verbose\n");
        printf("\t -i\t interactive\n");
        printf("\t -f\t force\n");
        printf("\t -p\t preserve\n");
        printf("\n");
        return 0;
    }

    if (argc <= optind + 1)
    {
        printf("Too few arguments\n");
        return 0;
    }

    cp(argv[optind], argv[optind + 1], flag_v, flag_i, flag_f, flag_p);
    return 0;
}