#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L

/** Sorts an input array using bubble sort
 *  Returns the time taken to sort the array */
uint64_t bubble_sort (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}

/** Sorts an input array using bubble sort and parallel processing
 *  Returns the time taken to sort the array */
uint64_t bubble_sort_parallel (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int i, t, s = 1;
    while (s) {
        s = 0;
        #pragma omp parallel for
        for (i = 1; i < n; i++) {
            #pragma omp critical
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}
