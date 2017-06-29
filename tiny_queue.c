#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include "tiny_queue.h"

// Create a queue, return a pointer to tiny_queue_t
tiny_queue_t* tiny_queue_create() {
  struct tiny_queue_t* queue = (struct tiny_queue_t*)malloc(sizeof(struct tiny_queue_t));
  queue->head = NULL;
  queue->tail = NULL;

  queue->mutex  = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  queue->wakeup = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  return queue;
}

// Push a pointer onto the queue
void tiny_queue_push(tiny_queue_t *queue, void *x) {
  pthread_mutex_lock(&queue->mutex);
    struct tiny_linked_list_t* new_node = (struct tiny_linked_list_t*)malloc(sizeof(struct tiny_linked_list_t));
    new_node->data = x;
    new_node->next = NULL;

    if(queue->head == NULL && queue->tail == NULL){
      queue->head = queue->tail = new_node;
    } else {
      queue->tail->next = new_node;
      queue->tail = new_node;
    }
  pthread_mutex_unlock(&queue->mutex);
  pthread_cond_signal(&queue->wakeup);
}

// Pop a pointer from the queue
void *tiny_queue_pop(tiny_queue_t *queue) {
  pthread_mutex_lock(&queue->mutex);
    while(queue->head == NULL) { // block if buffer is empty
      pthread_cond_wait(&queue->wakeup, &queue->mutex);
    }

    struct tiny_linked_list_t* current_head = queue->head;
    void *data = current_head->data;
    if(queue->head == queue->tail) {
      queue->head = queue->tail = NULL;
    }
    else {
      queue->head = queue->head->next;
    }
    free(current_head);
  pthread_mutex_unlock(&queue->mutex);

  return data;
}
