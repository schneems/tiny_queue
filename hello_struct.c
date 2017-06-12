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
  struct city_t* austin = (struct city_t*)malloc(sizeof(struct city_t));
  austin->name = "Austin";
  austin->rank = 1;
  tiny_queue_push(my_queue, austin);

  struct city_t* atlanta = (struct city_t*)malloc(sizeof(struct city_t));
  atlanta->name = "Atlanta";
  atlanta->rank = 2;
  tiny_queue_push(my_queue, atlanta);


  city_t *city1 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city1->name, city1->rank);

  city_t *city2 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city2->name, city2->rank);
}