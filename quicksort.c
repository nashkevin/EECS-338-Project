#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L
 
uint64_t quicksort(int *A, int len) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (len < 2) 
        return 0;
 
    int pivot = A[len / 2];
 
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] < pivot) 
            i++;
        while (A[j] > pivot) 
            j--;

        if (i >= j) 
            break;

        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    quicksort(A, i);
    quicksort(A + i, len - i);

    clock_gettime(CLOCK_MONOTONIC, &end);
    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

struct arg_struct {
    int *a;
    int n;
};

void *quicksort_thread(void *arguments) {
    struct arg_struct *args = arguments;
    int *A = args -> a;
    int len = args -> n;

    if (len < 2) 
        return 0;
 
    int pivot = A[len / 2];
 
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] < pivot) 
            i++;
        while (A[j] > pivot) 
            j--;

        if (i >= j) 
            break;

        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    quicksort(A, i);
    quicksort(A + i, len - i);

    pthread_exit(0);
}

uint64_t quicksort_parallel (int *A, int len) {

    pthread_t tid1, tid2;
    struct arg_struct args1, args2;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (len < 2) 
        return 0;
 
    int pivot = A[len / 2];
 
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] < pivot) 
            i++;
        while (A[j] > pivot) 
            j--;

        if (i >= j) 
            break;

        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    args1.a = A;
    args1.n = i;
    if (pthread_create(&tid1, NULL, &quicksort_thread, (void *)&args1) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }    
    args2.a = A + i;
    args2.n = len - i;
    if (pthread_create(&tid2, NULL, &quicksort_thread, (void *)&args2) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}