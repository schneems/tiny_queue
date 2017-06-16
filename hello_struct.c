#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tiny_queue.h"

typedef struct city_t {
  char *name;
  int rank;
} city_t;

int main(){
  tiny_queue_t *my_queue = tiny_queue_create();

  if (my_queue == NULL) {
    fprintf(stderr, "Cannot create the queue\n");
    return -1;
  }

  // Push values.
  struct city_t* austin = (struct city_t*)malloc(sizeof(struct city_t));
  austin->name = "Austin";
  austin->rank = 1;
  if (tiny_queue_push(my_queue, austin) != 0) {
    fprintf(stderr, "Cannot push a value in the queue\n");
    return -1;
  }

  struct city_t* atlanta = (struct city_t*)malloc(sizeof(struct city_t));
  atlanta->name = "Atlanta";
  atlanta->rank = 2;
  if (tiny_queue_push(my_queue, atlanta) != 0) {
    fprintf(stderr, "Cannot push a value in the queue\n");
    return -1;
  }

  // Pop values
  city_t *city1 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city1->name, city1->rank);

  city_t *city2 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city2->name, city2->rank);

  if (tiny_queue_destroy(my_queue) != 0) {
    fprintf(stderr, "Cannot destroy the queue, but it doesn't matter becaus");
    fprintf(stderr, "e the program will exit instantly\n");
    return -1;
  } else {
    return 1;
  }
}
