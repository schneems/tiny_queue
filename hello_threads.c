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


void *do_work(void *arg) {
  // Store queue argument as new variable
  tiny_queue_t *my_queue = arg;

  // Pop work off of queue, thread blocks here till queue has work
  work_t *work = tiny_queue_pop(my_queue);

  // Do work
  printf("Working on %s %s\n", work->a, work->b);

  return 0;
}

int main(){
  pthread_t threadpool[NUMTHREADS];
  int i;

  // Create new queue
  tiny_queue_t *my_queue = tiny_queue_create();

  // Create thread pool
  for (i=0; i < NUMTHREADS; i++) {
    // Pass queue to new thread
    if (pthread_create(&threadpool[i], NULL, do_work, my_queue) != 0) {
      fprintf(stderr, "Unable to create worker thread\n");
      return -1;
    }
  }

  // Push "work" onto queue
  for (i=0; i < NUMTHREADS; i++) {
    printf("num %i\n", i);
    struct work_t* work = (struct work_t*)malloc(sizeof(struct work_t));

    sprintf(work->a, "string_%i", i); // puts string into buffer
    sprintf(work->b, "string_%i", i + 1); // puts string into buffer

    // Every time an item is added to the queue, a thread that is
    // Blocked by `tiny_queue_pop` will unblock
    tiny_queue_push(my_queue, work);
  }

  // sleep(4);


  // Join all the threads
  for (i=0; i < NUMTHREADS; i++) {
    pthread_join(threadpool[i], NULL); // wait for producer to exit
  }
}
