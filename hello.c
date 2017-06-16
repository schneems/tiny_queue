#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "tiny_queue.h"

int main(){
  tiny_queue_t *my_queue = tiny_queue_create();

  // Push the values.
  if (my_queue == NULL) {
    fprintf(stderr, "Cannot allocate queue\n");
    return -1;
  }

  char *a = "hello";
  if (tiny_queue_push(my_queue, a) != 0) {
    fprintf(stderr, "Cannot push %s in the queue\n", a);
    return -1;
  }

  char *b = "there";
  if (tiny_queue_push(my_queue, b) != 0) {
    fprintf(stderr, "Cannot push %s in the queue\n", b);
    return -1;
  }

  char *c = "neighbor";
  if (tiny_queue_push(my_queue, c) != 0) {
    fprintf(stderr, "Cannot push %s in the queue\n", c);
    return -1;
  }

  // Pop the values.
  char *result;

  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);

  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);

  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);

  if (tiny_queue_destroy(my_queue) != 0) {
    fprintf(stderr, "Cannot destroy the queue, but it doesn't matter becaus");
    fprintf(stderr, "e the program will exit instantly\n");
    return -1;
  } else {
    return 0;
  }
}
