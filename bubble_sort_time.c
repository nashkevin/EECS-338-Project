#include <stdio.h>
#include <stdlib.h>
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

int real_main(){
    char *filename = "bubble_sort.csv"
    FILE *fp;
    fp=fopen(filename,"w");
    fprintf(fp,"N, Time(ns)");


    time_t begin, end;
    int i, n;
    for (n = 10; n < 10000; n++){
        int *array = random_array(n)

        if (array) {
            begin = clock();
            bubble_sort(array, n);
            end = clock();

            if (is_sorted(array)) {
                fprintf(fp,"\n%d,%d", n, ((end - begin)) * 1000 * 1000 / CLOCKS_PER_SEC));
            }

            free(array);
        }
    }
}

int main () {
    time_t begin, end;
    int *a = random_array(30);
    int n = 30;
    int i;
    if (a) {
        for (i = 0; i < n; i++)
            printf("%d%s", a[i], i == n - 1 ? "\n" : " ");

        begin = clock(); //starts clock
        bubble_sort(a, n); //runs bubble sort
        end = clock(); //stops clock

        for (i = 0; i < n; i++)
            printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
        printf("Execution time of bubble sort: %d nanoseconds.\n", ((end - begin)) * 1000 * 1000 / CLOCKS_PER_SEC);
    
        free(a);
    }

    int *b = random_array(20);
    if (b) {
        for (i = 0; i < n; i++)
            printf("%d%s", b[i], i == n - 1 ? "\n" : " ");

        begin = clock(); //starts clock
        threaded_bubble_sort(b, n); //runs threaded bubble sort
        end = clock(); //stops clock

        for (i = 0; i < n; i++)
            printf("%d%s", b[i], i == n - 1 ? "\n" : " ");
        printf("Execution time of threaded bubble sort: %d nanoseconds.\n", ((end - begin)) * 1000 * 1000 / CLOCKS_PER_SEC);

        free(b);
    }
    return 0;
}