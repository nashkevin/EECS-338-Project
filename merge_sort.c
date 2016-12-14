#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L

void merge (int *a, int n, int m) {
    int i, j, k;
    int *x = malloc(n * sizeof (int));
    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n      ? a[i++]
             : i == m      ? a[j++]
             : a[j] < a[i] ? a[j++]
             :               a[i++];
    }
    for (i = 0; i < n; i++) {
        a[i] = x[i];
    }
    free(x);
}
 
uint64_t merge_sort (int *a, int n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (n < 2)
        return 0;
    int m = n / 2;
    merge_sort(a, m);
    merge_sort(a + m, n - m);
    merge(a, n, m);

    clock_gettime(CLOCK_MONOTONIC, &end);
    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

struct arg_struct {
    int *a;
    int n;
};

void *merge_sort_thread(void *arguments) {
    struct arg_struct *args = arguments;
    int *a = args -> a;
    int n = args -> n;

    if (n < 2)
        return 0;
    int m = n / 2;
    merge_sort(a, m);
    merge_sort(a + m, n - m);
    merge(a, n, m);

    pthread_exit(0);
}

uint64_t merge_sort_parallel (int *a, int n) {

    pthread_t tid1, tid2;
    struct arg_struct args1, args2;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (n < 2)
        return 0;
    int m = n / 2;


    args1.a = a;
    args1.n = m;
    if (pthread_create(&tid1, NULL, &merge_sort_thread, (void *)&args1) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }
    args2.a = a + m;
    args2.n = n - m;
    if (pthread_create(&tid2, NULL, &merge_sort_thread, (void *)&args2) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    merge(a, n, m);

    clock_gettime(CLOCK_MONOTONIC, &end);
    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}
