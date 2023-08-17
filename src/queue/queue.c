//#define QUEUE_ELEMENT_T int
//#define QUEUE_ELEMENT_T int
// dummy, just for compiling

#ifndef QUEUE_ELEMENT_T
#define QUEUE_ELEMENT_T int
#endif

#include "./queue.h"

void QUEUE_Ctor(TQueue *const q) {
    q->front = -1;
    q->rear = -1;
}

bool QUEUE_Enqueue(TQueue *const q, QUEUE_ELEMENT_T elem) {
    printf("%d %d %d\n", q->front, q->rear, MAX_QUEUE_CAPACITY);
    if (QUEUE_IsFull(q)) {
        return false;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_CAPACITY;
    q->elements[q->rear] = elem;
    if (q->front == -1) {
        q->front = 0;
    }
    return true;
}

QUEUE_ELEMENT_T QUEUE_Dequeue(TQueue *const q) {
    if (QUEUE_IsEmpty(q)) {
        // Return a default value; needs to be adapted based on the actual type of QUEUE_ELEMENT_T.
        // You might want to provide an error-handling mechanism here.
        return (QUEUE_ELEMENT_T){0};
    }
    QUEUE_ELEMENT_T item = q->elements[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_CAPACITY;
    }
    return item;
}

int8_t QUEUE_GetSize(TQueue *const q) {
    if (q->front == -1) {
        return 0;
    }
    if (q->rear >= q->front) {
        return q->rear - q->front + 1;
    } else {
        return (MAX_QUEUE_CAPACITY - q->front) + (q->rear + 1);
    }
}

QUEUE_ELEMENT_T QUEUE_Peek(TQueue *const q) {
    if (QUEUE_IsEmpty(q)) {
        // Return a default value; needs to be adapted based on the actual type of QUEUE_ELEMENT_T.
        // You might want to provide an error-handling mechanism here.
        return (QUEUE_ELEMENT_T){0};
    }
    return q->elements[q->front];
}

bool QUEUE_IsFull(TQueue *const q) {
    return (((q->rear + 1) % MAX_QUEUE_CAPACITY) == q->front);
}

bool QUEUE_IsEmpty(TQueue *const q) {
    return (q->front == -1);
}
