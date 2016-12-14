#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L

/** Sorts an input array using insertion sort
 *  Returns the time taken to sort the array */
uint64_t insertion_sort (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

    size_t i, j;
    for (i = 1; i < n; ++i) {
        int tmp = a[i];
        j = i;
        while (j > 0 && tmp < a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = tmp;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}

/** Sorts an input array using insertion sort and parallel processing
 *  Returns the time taken to sort the array */
uint64_t insertion_sort_parallel (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    size_t i, j;
    #pragma omp parallel for
    for (i = 1; i < n; ++i) {
        int tmp = a[i];
        j = i;
        #pragma omp critical
        while (j > 0 && tmp < a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = tmp;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}
