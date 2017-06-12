#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

typedef struct tiny_queue_t {
  struct tiny_lined_list_t* head;
  struct tiny_lined_list_t* rear;
  pthread_mutex_t mutex;
  pthread_cond_t wakeup;
} tiny_queue_t;

typedef struct tiny_lined_list_t {
  void *data;
  struct tiny_lined_list_t* next;
} tiny_lined_list_t;

tiny_queue_t* tiny_queue_create() {
  struct tiny_queue_t* queue = (struct tiny_queue_t*)malloc(sizeof(struct tiny_queue_t));
  queue->head = NULL;
  queue->rear = NULL;

  queue->mutex  = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  queue->wakeup = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
  return queue;
}

void tiny_queue_push(tiny_queue_t *queue, void *x) {
  pthread_mutex_lock(&queue->mutex);
    struct tiny_lined_list_t* new_node = (struct tiny_lined_list_t*)malloc(sizeof(struct tiny_lined_list_t));
    new_node->data = x;
    new_node->next = NULL;

    if(queue->head == NULL && queue->rear == NULL){
      queue->head = queue->rear = new_node;
    } else {
      queue->rear->next = new_node;
      queue->rear = new_node;
    }
  pthread_mutex_unlock(&queue->mutex);
  pthread_cond_signal(&queue->wakeup);
}

void *tiny_queue_pop(tiny_queue_t *queue) {
  pthread_mutex_lock(&queue->mutex);
    while(queue->head == NULL) { // block if buffer is empty
      pthread_cond_wait(&queue->wakeup, &queue->mutex);
    }

    struct tiny_lined_list_t* current_head = queue->head;
    void *data = current_head->data;
    if(queue->head == queue->rear) {
      queue->head = queue->rear = NULL;
    }
    else {
      queue->head = queue->head->next;
    }
    free(current_head);
  pthread_mutex_unlock(&queue->mutex);

  return data;
}