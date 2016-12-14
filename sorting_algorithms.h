#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <stdint.h>

uint64_t bubble_sort (int *a, int n);
uint64_t bubble_sort_parallel (int *a, int n);
uint64_t insertion_sort (int *a, int n);
uint64_t insertion_sort_parallel (int *a, int n);
uint64_t merge_sort (int *a, int n);
uint64_t merge_sort_parallel (int *a, int n);
uint64_t selection_sort (int *a, int n);
uint64_t selection_sort_parallel (int *a, int n);
uint64_t quicksort (int *a, int n);
uint64_t quicksort_parallel (int *a, int n);

#endif
