#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "tiny_queue.h"

#define NUMTHREADS 4

typedef struct work_t {
  char a[1024];
  char b[1024];
} work_t;

tiny_queue_t *global_queue;

void *do_work(void *arg) {
  // Pop work off of queue, thread blocks here till queue has work
  work_t *work = tiny_queue_pop(global_queue);

  // Do work
  printf("Working on %s %s\n", work->a, work->b);

  return 0;
}

int main(){
  pthread_t threadpool[NUMTHREADS];
  global_queue = tiny_queue_create();
  int i;

  // Create thread pool
  for (i=0; i < NUMTHREADS; i++) {
    if (pthread_create(&threadpool[i], NULL, do_work, NULL) != 0) {
      fprintf(stderr, "Unable to create worker thread\n");
      return -1;
    }
  }

  for (i=0; i < NUMTHREADS; i++) {
    printf("num %i\n", i);
    struct work_t* work = (struct work_t*)malloc(sizeof(struct work_t));

    sprintf(work->a, "string_%i", i); // puts string into buffer
    sprintf(work->b, "string_%i", i + 1); // puts string into buffer
    tiny_queue_push(global_queue, work);
  }

  // sleep(4);


  // join
  for (i=0; i < NUMTHREADS; i++) {
    pthread_join(threadpool[i], NULL); // wait for producer to exit
  }
}
