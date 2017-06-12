#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "tiny_queue.h"

int main(){
  tiny_queue_t *my_queue = tiny_queue_create();
  char *a = "hello";
  tiny_queue_push(my_queue, a);
  char *b = "there";
  tiny_queue_push(my_queue, b);
  char *c = "neighbor";
  tiny_queue_push(my_queue, c);

  char *result;
  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);

  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);

  result = tiny_queue_pop(my_queue);
  printf("Popped: %s\n", result);
}
