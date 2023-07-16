#include <stdbool.h>

#define QUEUE_SIZE 10

#define DECLARE_QUEUE(type) \
    typedef struct { \
        int front; \
        int rear; \
        type array[QUEUE_SIZE]; \
    } Queue_##type; \
    \
    void init_##type(Queue_##type *q) { \
        q->front = -1; \
        q->rear = -1; \
    } \
    \
    bool enqueue_##type(Queue_##type *q, type item) { \
        if (q->rear == QUEUE_SIZE - 1) return false; \
        if (q->front == -1) \
            q->front = 0; \
        q->rear++; \
        q->array[q->rear] = item; \
        return true; \
    } \
    \
    type dequeue_##type(Queue_##type *q) { \
        if (q->front == -1 || q->front > q->rear) return 0; \
        type val = q->array[q->front]; \
        q->front++; \
        return val; \
    }

DECLARE_QUEUE(int)