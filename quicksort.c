#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "sorting_algorithms.h"
 
long quicksort(int *A, int len) {
    time_t startTime, endTime;
    startTime = clock();

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

    endTime = clock();
    return (long)((endTime - startTime) * 1000 * 1000 / CLOCKS_PER_SEC);
}