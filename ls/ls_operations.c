#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <strings.h>

int main(int argc, char** argv) {
    
    const struct option long_option[] =
    {
        {"add", no_argument, NULL, 'a'},
        {"sub", no_argument, NULL, 's'}, 
        {"mul", no_argument, NULL, 'm'},
        {"div", no_argument, NULL, 'd'},
        {NULL, no_argument, NULL, 0}
    };
	int long_index;
    int opt;
    const char short_option[] = "asmd";
    
    int flag_a = 0, flag_s = 0, flag_m = 0, flag_d = 0;
    
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'a': flag_a = 1;
            break;
        case 's': flag_s = 1;
            break;
        case 'm': flag_m = 1;
            break;
        case 'd': flag_d = 1;
        case '?': printf("Unknown parameter: -%c\n", optopt);
        }
    }

    int a = atoi(argv[optind]);
    int b = atoi(argv[optind + 1]);
    int res = 0;

    if (flag_a == 1) {
        res = a + b;
    }

    if (flag_s == 1) {
        res = a - b;
    }
    
    if (flag_m == 1) {
        res = a * b;
    }

    if (flag_d == 1) {
        res = a / b;
    }

    printf("res = %d\n", res);

    return 0;
}
