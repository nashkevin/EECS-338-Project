#include <stdio.h>
#include <time.h>
#include <omp.h>  

void threaded_bubble_sort (int *a, int n) {
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
}
 
void bubble_sort (int *a, int n) {
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
}

int main () {
    clock_t begin, end;
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    int i;
    for (i = 0; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

    begin = clock(); //starts clock
    bubble_sort(a, n); //runs bubble sort
    end = clock(); //stops clock

    for (i = 0; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    printf("Execution time of bubble sort: %d.\n", (double)(end - begin) / CLOCKS_PER_SEC);
    


    int b[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1}; //prepares a new array to be sorted
    for (i = 0; i < n; i++)
        printf("%d%s", b[i], i == n - 1 ? "\n" : " ");

    begin = clock(); //starts clock once again
    threaded_bubble_sort(b, n); //runs threaded bubble sort
    end = clock(); //stops clock once again

    for (i = 0; i < n; i++)
        printf("%d%s", b[i], i == n - 1 ? "\n" : " ");
    printf("Execution time of threaded bubble sort: %d.\n", (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}