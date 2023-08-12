#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

#include "./queue.h"

#define QUEUE_IMPLEMENTATION(T, maxQueueCapacity) \
    void QUEUE_##T##_Ctor(QUEUE_##T *const q) { \
        q->front = -1; \
        q->rear = -1; \
    } \
    \
    void QUEUE_##T##_Enqueue(QUEUE_##T *const q, T item) { \
        if (((q->rear + 1) % maxQueueCapacity) == q->front) { \
            printf("Queue is full. Cannot enqueue.\n"); \
            return; \
        } \
        q->rear = (q->rear + 1) % maxQueueCapacity; \
        q->elements[q->rear] = item; \
        if (q->front == -1) { \
            q->front = 0; \
        } \
    } \
    \
    T QUEUE_##T##_Dequeue(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot dequeue.\n"); \
            return (T){0}; \
        } \
        T item = q->elements[q->front]; \
        if (q->front == q->rear) { \
            q->front = -1; \
            q->rear = -1; \
        } else { \
            q->front = (q->front + 1) % maxQueueCapacity; \
        } \
        return item; \
    } \
    \
    int QUEUE_##T##_GetSize(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            return 0; \
        } \
        if (q->rear >= q->front) { \
            return q->rear - q->front + 1; \
        } else { \
            return (maxQueueCapacity - q->front) + (q->rear + 1); \
        } \
    } \
    \
    T QUEUE_##T##_Peek(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot peek.\n"); \
            return (T){0}; \
        } \
        return q->elements[q->front]; \
    } \
    \
    bool QUEUE_##T##_IsFull(QUEUE_##T *const q) { \
        return (((q->rear + 1) % maxQueueCapacity) == q->front); \
    }

#endif // QUEUE_IMPL_H
