#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tiny_queue.h"

typedef struct city_t {
  char *name;
  int rank;
} city_t;

// Create a new structure (like constructors in OOP).
struct city_t *city_new(char *name, int rank) {
  struct city_t *city = (struct city_t*)malloc(sizeof(struct city_t));

  if (city == NULL)
    return NULL;

  city->name = calloc(1 + strlen(name), sizeof(char)); // string's length + '\0'
  strcat(city->name, name);

  city->rank = rank;

  return city;
}

// Destroy the structure.
// It is better to use a pointer to pointer because you can check if the pointer
// is NULL in the code, to avoid unwanted operations.
void city_destroy(struct city_t **city) {
  free((*city)->name);

  free(*city);
  *city = NULL;
}

int main(){
  tiny_queue_t *my_queue = tiny_queue_create();

  if (my_queue == NULL) {
    fprintf(stderr, "Cannot create the queue\n");
    return -1;
  }

  // Push values.
  struct city_t *austin = city_new("Austin", 1);
  if (austin == NULL) {
    fprintf(stderr, "Cannot create a structure\n");
    return -1;
  }

  if (tiny_queue_push(my_queue, austin) != 0) {
    fprintf(stderr, "Cannot push the structure in the queue\n");
    return -1;
  }

  printf("okk\n");

  struct city_t *atlanta = city_new("Atlanta", 2);
  if (atlanta == NULL) {
    fprintf(stderr, "Cannot create a structure\n");
    return -1;
  }

  if (tiny_queue_push(my_queue, atlanta) != 0) {
    fprintf(stderr, "Cannot push a value in the queue\n");
    return -1;
  }

  // Pop and destroy values
  city_t *city1 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city1->name, city1->rank);
  city_destroy(&city1);

  city_t *city2 = tiny_queue_pop(my_queue);
  printf("Popped: %s ranked %i\n", city2->name, city2->rank);
  city_destroy(&city2);

  if (tiny_queue_destroy(my_queue) != 0) {
    fprintf(stderr, "Cannot destroy the queue, but it doesn't matter becaus");
    fprintf(stderr, "e the program will exit instantly\n");
    return -1;
  } else {
    return 1;
  }
}
