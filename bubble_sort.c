#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"

/** Sorts an input array using bubble sort
 *  Returns the time taken to sort the array */
long bubble_sort (int *a, int n) {
    time_t startTime, endTime;
    startTime = clock();

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

    endTime = clock();
    return (long)((endTime - startTime) * 1000 * 1000 / CLOCKS_PER_SEC);
}

/** Sorts an input array using bubble sort and parallel processing
 *  Returns the time taken to sort the array */
long bubble_sort_parallel (int *a, int n) {
    time_t startTime, endTime;

    startTime = clock();
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

    endTime = clock();
    return (long)((endTime - startTime) * 1000 * 1000 / CLOCKS_PER_SEC);
}
