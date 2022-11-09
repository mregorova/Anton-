#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double integral(double sum, double l, double r, double dx, long count)
{
    double x = dx;

    for (int i = 1; i < count; i++) {
        sum += dx*(sqrt(4 - x*x));
        x += dx;
    }

    return sum;
}

int main(int argc, char* argv[])
{
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    if(argc != 2) {
        printf("Too few arguments!\n");
        return 1;
    }

    long count = atoi(argv[1]);
    double sum = 0, l = 0, r = 2, dx = 2.0 / count;

    printf("%f\n", integral(sum, l, r, dx, count));
    gettimeofday(&tv2, NULL);
    printf ("Time = %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    
    return 0;
}