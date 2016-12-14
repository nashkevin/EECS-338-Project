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