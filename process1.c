#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main(int  argc, char** argv)
{   
    strtoi(argv[]);
    int t, n, sum = 0;
    int fd[2];
    pipe(fd);
    pid_t f = fork();
    if (f != 0)
    {
        close(fd[0]);
        scanf("%d", &n);
        write(fd[1], &n, sizeof(int));
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &t);
            write(fd[1], &t, sizeof(int));
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        read(fd[0], &n, sizeof(int));
        for (int i = 0; i < n; i++)
        {
            read(fd[0], &t, sizeof(int));
            sum += t;
        }
        printf("%d\n", sum);
        close(fd[0]);
    }
    return 0;
}
