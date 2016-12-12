#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

/** Sorts an input array using insertion sort
 *  Returns the time taken to sort the array */
long insertion_sort (int *a, int n) {
    time_t startTime, endTime;
    startTime = clock();

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

    endTime = clock();
    return (long)((endTime - startTime) * 1000 * 1000 / CLOCKS_PER_SEC);
}

/** Sorts an input array using insertion sort and parallel processing
 *  Returns the time taken to sort the array */
long insertion_sort_parallel (int *a, int n) {
    time_t startTime, endTime;

    startTime = clock();
    
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

    endTime = clock();
    return (long)((endTime - startTime) * 1000 * 1000 / CLOCKS_PER_SEC);
}
