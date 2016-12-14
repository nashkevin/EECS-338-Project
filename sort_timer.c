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

void time_to_file(char *filename, uint64_t (*f_regular)(int[], int), uint64_t (*f_parallel)(int[], int)){
    FILE *fp;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "w");
    fprintf(fp, "N, Regular Sort, Parallel Sort");

    int i, n;
    for (n = 1; n < 100000; n += 1000) {
        int *array1 = random_array(n);
        int *array2 = random_array(n);

        if (array) {
            uint64_t t_regular = (*f_regular)(array1, n);
            uint64_t t_parallel = (*f_parallel)(array2, n);

            fpringf(fp, "\n%d", n);

            if (is_sorted(array1, n)) {
                fprintf(fp,",%llu", t_regular);
            } else {
                fprintf(fp,", NOTSORTED");
            }

            if (is_sorted(array2, n)) {
                fprintf(fp,",%llu", t_parallel);
            } else {
                fprintf(fp,", NOTSORTED");
            }

            free(array1);
            free(array2);
        }
    }

    fclose(fp);
}

int main(void) {
    char bubble_sort_filename[] = "bubble_sort";
    time_to_file(bubble_sort_filename, bubble_sort, bubble_sort_parallel);
    char insertion_sort_filename[] = "insertion_sort";
    time_to_file(insertion_sort_filename, insertion_sort, insertion_sort_parallel);
    char merge_sort_filename[] = "merge_sort";
    time_to_file(merge_sort_filename, merge_sort, merge_sort_parallel);
    char selection_sort_filename[] = "selection_sort";
    time_to_file(selection_sort_filename, selection_sort, selection_sort_parallel);
    char quicksort_filename[] = "quicksort";
    time_to_file(quicksort_filename, quicksort, quicksort_parallel);
    return 0;
}
