#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sorting_algorithms.h"

int is_sorted (int *a, int n) {
    int i;
    for (i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int *random_array(int n) {
    int *ret = malloc(n * sizeof(int));
    if (!ret) {
        return NULL;
    }

    srand(time(NULL));

    int i;
    for(i = 0; i < n; ++i) {
        ret[i] = rand() % n;
    }

    return ret;
}

void time_to_file(char *filename, uint64_t (*f)(int[], int)){
    FILE *fp;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "w");
    fprintf(fp, "N, Time(ns)");

    int i, n;
    for (n = 1; n < 100000; n += 1000){
        int *array = random_array(n);

        if (array) {
            uint64_t t = (*f)(array, n);

            if (is_sorted(array, n)) {
                fprintf(fp,"\n%d,%llu", n, t);
            } else {
                fprintf(fp,"\n%d, NOTSORTED", n);
            }

            free(array);
        }
    } 

    fclose(fp);
}

int main(void) {
    char bubble_sort_filename[] = "bubble_sort";
    time_to_file(bubble_sort_filename, bubble_sort);
    char bubble_sort_parallel_filename[] = "bubble_sort_parallel";
    time_to_file(bubble_sort_parallel_filename, bubble_sort_parallel);
    char insertion_sort_filename[] = "insertion_sort";
    time_to_file(insertion_sort_filename, insertion_sort);
    char insertion_sort_parallel_filename[] = "insertion_sort_parallel";
    time_to_file(insertion_sort_parallel_filename, insertion_sort_parallel);
    char merge_sort_filename[] = "merge_sort";
    time_to_file(merge_sort_filename, merge_sort);
    char merge_sort_parallel_filename[] = "merge_sort_parallel";
    time_to_file(merge_sort_parallel_filename, merge_sort_parallel);
    char selection_sort_filename[] = "selection_sort";
    time_to_file(selection_sort_filename, selection_sort);
    char selection_sort_parallel_filename[] = "selection_sort_parallel";
    time_to_file(selection_sort_parallel_filename, selection_sort_parallel);
    char quicksort_filename[] = "quicksort";
    time_to_file(quicksort_filename, quicksort);
    char quicksort_parallel_filename[] = "quicksort_parallel";
    time_to_file(quicksort_parallel_filename, quicksort_parallel);
    return 0;
}
