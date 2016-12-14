#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define BILLION 1000000000L

int main(void) {
  time_t start, end;
  uint64_t diff;
  clock_gettime(CLOCK_MONOTONIC, &start);

  sleep(5);
  int i;
  for (i = 0; i < 1000; i ++)
    ;

  clock_gettime(CLOCK_MONOTONIC, &end);
  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
  printf("%d\n", diff);
  return 0;
}