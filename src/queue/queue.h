#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define QUEUE_MAX_CAPACITY 16 // should always be a power of 2

#define DECLARE_QUEUE(type) \
    typedef struct { \
        int8_t front; \
        int8_t rear; \
        type elements[QUEUE_MAX_CAPACITY]; \
    } QUEUE_ ##type; \
    \
    void QUEUE_##type##_Init(QUEUE_##type *q) { \
        q->front = -1; \
        q->rear = -1; \
    } \
    \
    void QUEUE_##type##_Enqueue(QUEUE_##type *q, type item) { \
        if (((q->rear + 1) & (QUEUE_MAX_CAPACITY - 1)) == q->front) { \
            printf("Queue is full. Cannot enqueue.\n"); \
            return; \
        } \
        \
        q->rear = (q->rear + 1) & (QUEUE_MAX_CAPACITY - 1); \
        q->elements[q->rear] = item; \
        if (q->front == -1) { \
            q->front = 0; \
        } \
    } \
    \
    type QUEUE_##type##_Dequeue(QUEUE_##type *q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot dequeue.\n"); \
            return (type){0}; \
        } \
        \
        type item = q->elements[q->front]; \
        if (q->front == q->rear) { \
            q->front = -1; \
            q->rear = -1; \
        } else { \
            q->front = (q->front + 1) & (QUEUE_MAX_CAPACITY - 1); \
        } \
        \
        return item; \
    } \
    \
    int QUEUE_##type##_GetSize(QUEUE_##type *q) { \
        if (q->front == -1) { \
            return 0; \
        } \
        \
        if (q->rear >= q->front) { \
            return q->rear - q->front + 1; \
        } else { \
            return (QUEUE_MAX_CAPACITY - q->front) + (q->rear + 1); \
        } \
    } \
    \
    type QUEUE_##type##_Peek(QUEUE_##type *q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot peek.\n"); \
            return (type){0}; \
        } \
        \
        return q->elements[q->front]; \
    }

    #endif
