#ifndef __TINY_QUEUE__
#define __TINY_QUEUE__

typedef struct tiny_queue_t {
  struct tiny_lined_list_t* head;
  struct tiny_lined_list_t* tail;
  pthread_mutex_t mutex;
  pthread_cond_t wakeup;
} tiny_queue_t;

typedef struct tiny_lined_list_t {
  void *data;
  struct tiny_lined_list_t* next;
} tiny_lined_list_t;

// Create an instance of tiny_queue
tiny_queue_t* tiny_queue_create();

// Push pointer onto tiny_queue, return -1 on error
int tiny_queue_push(tiny_queue_t *queue, void *x);

// Pop pointer from tiny_queue
void *tiny_queue_pop(tiny_queue_t *queue);

// Destroy the queue with all elements
int tiny_queue_destroy(tiny_queue_t *queue);
#endif
