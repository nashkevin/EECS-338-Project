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
    int *ret = malloc(n);
    if(!ret)
        return NULL;

    srand(time(NULL));

    for(int i = 0; i < n; ++i) 
        ret[i] = rand() % n;

    return ret;
}

void time_to_file(char *filename, void (*f)(int, int)){
    FILE *fp;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "w");
    fprintf(fp, "N, Time(ns)");

    int i, n;
    for (n = 10; n < 10000; n++){
        int *array = random_array(n);

        if (array) {
            long t = (*f)(array, n);

            if (is_sorted(array, n)) {
                fprintf(fp,"\n%d,%d", n, t);
            }

            free(array);
        }
    } 
}

void main() {
    time_to_file("bubble_sort", bubble_sort);
}