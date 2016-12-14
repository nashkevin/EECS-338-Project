#include <omp.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting_algorithms.h"

#define BILLION 1000000000L

sem_t mutex;

/** Sorts an input array using insertion sort
 *  Returns the time taken to sort the array */
uint64_t insertion_sort (int *a, int n) {
    struct timespec start, end;
    uint64_t diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

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

    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    return diff;
}

struct arg_struct {
    int *a;
    int n;
    struct node *x;
};

struct node {
  int val;
  struct node *next;
};

void *insertion_sort_thread(void *arguments){
    struct arg_struct *args = arguments;
    int *a = args -> a;
    int n = args -> n;
    struct node *x = args -> x;
    struct node *iterator = x;
    struct node *new_val = malloc(sizeof(struct node));

    int i;
    for (i = 0; i < n; i++) {
        new_val->val = a[i];
        new_val->next = NULL;
        sem_wait(&mutex);

        while(iterator -> next != NULL && iterator -> next -> val < a[i])
            iterator = iterator -> next;

        if (iterator -> next == NULL) {
            iterator->next = new_val;
        } else {
            new_val->next = iterator -> next;
            iterator->next = new_val;
        }

        sem_post(&mutex);
    }

}

/** Sorts an input array using insertion sort and parallel processing
 *  Returns the time taken to sort the array */
uint64_t insertion_sort_parallel (int *a, int n) {
    pthread_t tid1, tid2;
    struct arg_struct args1, args2;
    struct node *x = malloc(sizeof(struct node));

    if(sem_init(&mutex, 0, 1) < 0) {
        fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
        exit(0);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    x->val = a[0];

    if (n < 2) {
        return 0;
    }
    int m = n / 2;

    args1.a = a + 1;
    args1.n = m - 1;
    args1.x = x;
    args2.a = a + m;
    args2.n = n - m;
    args2.x = x;

    if (pthread_create(&tid1, NULL, &insertion_sort_thread, (void *)&args1) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }
    if (pthread_create(&tid2, NULL, &insertion_sort_thread, (void *)&args2) != 0) {
        printf("Uh-oh!\n");
        return -1;
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    struct node *iterator = x;
    struct node *temp;
    int i = 0;
    while(iterator -> next != NULL){
        a[i] = iterator -> val;
        temp = iterator;
        iterator = iterator -> next;
        free(temp);
        i++;
    }
    free(x);

    clock_gettime(CLOCK_MONOTONIC, &end);
    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}
