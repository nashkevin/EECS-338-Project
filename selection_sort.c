#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L

/** Sorts an input array using selection sort
 *  Returns the time taken to sort the array */
uint64_t selection_sort (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int i, j, m, t;
    for (i = 0; i < n; i++) {
        for (j = i, m = i; j < n; j++) {
            if (a[j] < a[m]) {
                m = j;
            }
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}

/** Sorts an input array using selection sort and parallel processing
 *  Returns the time taken to sort the array */
uint64_t selection_sort_parallel (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int i, j, m, t;
    for (i = 0; i < n; i++) {
        #pragma omp parallel for
        for (j = m = i; j < n; j++) {
            #pragma omp critical
            if (a[j] < a[m]) {
                m = j;
            }
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}
