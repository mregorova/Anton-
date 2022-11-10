#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef int pthread_barrierattr_t;
typedef struct {

    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int trip_count;

} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned int count) {
    
    if (count == 0) return -1;

    if (pthread_mutex_init(&barrier->mutex, 0) < 0) return -1;

    if (pthread_cond_init(&barrier->cond, 0) < 0) {
        pthread_mutex_destroy(&barrier->mutex);
        return -1;
    }

    barrier->trip_count = count;
    barrier->count = 0;

    return 0;
}

int pthread_barrier_destroy(pthread_barrier_t *barrier) {
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);

    return 0;
}

int pthread_barrier_wait(pthread_barrier_t *barrier) {

    pthread_mutex_lock(&barrier->mutex);
    ++(barrier->count);

    if (barrier->count >= barrier->trip_count) {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
        pthread_mutex_unlock(&barrier->mutex);

        return 1;
    }

    else {
        pthread_cond_wait(&barrier->cond, &(barrier->mutex));
        pthread_mutex_unlock(&barrier->mutex);
        return 0;
    }
}

pthread_barrier_t barrier;

double** u = 0;
int* hf = 0;
int* ht = 0;
double M = 0;
int N = 0;

void* calculate(void *arg) {

    int l = *((int *)arg);
    for (int i = 1; i < M; i++) {

        pthread_barrier_wait(&barrier);
        for (int j = hf[l]; j < ht[l]; j++) {
            u[i % 2][j] = u[(i - 1) % 2][j] + 0.3 * (u[(i - 1) % 2][j + 1] - 2 * u[(i - 1) % 2][j] + u[(i - 1) % 2][j - 1]);
        }
    }
    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char* argv[]) {

    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    if (argc != 4) {
        printf("Too few arguments\n");
        return 1;
    }

    N = atoi(argv[1]);
    double T = atof(argv[2]);
    int TNUM = atoi(argv[3]);
    double h = 1 / (double) N;
    M = (T * N * N) / 0.3;

    u = (double**)malloc(2 * sizeof(double*));
    int* inc = (int*)malloc(TNUM*sizeof(int));
    hf = (int*)malloc(TNUM*sizeof(int));
    ht = (int*)malloc(TNUM*sizeof(int));

    for (int i = 0; i < 2; i++) u[i] = (double*)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) u[0][i] = 0;

    u[0][0] = 0;
    u[1][0] = 0;
    u[0][N - 1] = 1;
    u[1][N - 1] = 1;

    pthread_barrier_init(&barrier, NULL, TNUM);
    pthread_t tt[TNUM];

    for (int i = 0; i < TNUM; i++) {

        inc[i] = i;
        hf[i] = (N * i) / TNUM;
        ht[i] = (N * (i + 1)) / TNUM;

        if (i == 0) hf[i]++;
        if (i == TNUM - 1) ht[i]--;

        pthread_create(&tt[i], NULL, calculate, &inc[i]);
    }

    for (int i = 0; i < TNUM; i++) pthread_join(tt[i], NULL);

    gettimeofday(&tv2, NULL);
    printf ("Time = %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    
    FILE* f = fopen("thread.txt", "w");
    for (int i = 0; i < N; i++) fprintf(f,"%f\t%f\n", i*h, u[(int)M % 2][i]);

    return 0;

    fclose(f);
    free(inc);
    free(hf);
    free(ht);

    for (int i = 0; i < 2; i++) free(u[i]);
    free(u);
}