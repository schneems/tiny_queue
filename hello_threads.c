#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "tiny_queue.h"

#define NUMTHREADS 10

// The queue accepts pointers so we can pass arbitrary structs into our queue.
typedef struct work_t {
  int a;
  int b;
} work_t;

// This function will be passed in to `pthread_create`
void *do_work(void *arg) {
  // Store queue argument as new variable
  tiny_queue_t *my_queue = arg;

  // Pop work off of queue, thread blocks here till queue has work
  work_t *work = tiny_queue_pop(my_queue);

  // Do work, we're not really doing anything here, but you
  // could
  printf("(%i * %i) = %i\n", work->a, work->b, work->a * work->b);
  free(work);
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

  // Produce "work" and add it on to the queue
  for (i=0; i < NUMTHREADS; i++) {
    // Allocate an object to push onto queue
    struct work_t* work = (struct work_t*)malloc(sizeof(struct work_t));
    work->a = i+1;
    work->b = 2 *(i+1);

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
