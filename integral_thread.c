#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

int num = 0;
long count = 0;
double* sum = 0;
double* x = 0;
double dx = 0;

void* integral(void *arg) {

    int l = *((int *)arg);
    double d = x[l];
    double sum1 = 0;

    for (int i = 1; i < count/num; i++)
    {
        d += dx;
        sum1 += sqrt(4-d*d);
    }

    sum1 *= dx;
    sum[l] = sum1;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    if (argc != 3)
    {
        printf("Too few arguments\n");
        return 1;
    }

    double res = 0;
    int* inc = 0;
    count = atoi(argv[1]);
    num = atoi(argv[2]);
    dx = 2.0 / count;

    inc = (int*)malloc(num* sizeof(int));
    x = (double*)malloc(num* sizeof(double));
    sum = (double*)malloc(num* sizeof(double));

    for (int i = 0; i < num; i++) {
        sum[i] = 0;
        inc[i] = i;
        x[i] = i*(2.0/num);
    }

    x[num] = 2.0;
    pthread_t t[num];

    for (int i = 0; i < num; i++) {
        pthread_create(&t[i], NULL, integral, &inc[i]);
    }

    for (int i = 0; i < num; i++) {
        pthread_join(t[i], NULL);
    }

    for (int i = 0; i < num; i++) {
        res += sum[i];
    }

    printf("%f\n", res);
    gettimeofday(&tv2, NULL);
    printf ("Time = %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    
    free(inc);
    free(x);
    free(sum);

    return 0;
}