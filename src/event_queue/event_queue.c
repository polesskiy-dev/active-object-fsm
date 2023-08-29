#include "./event_queue.h"

#include "event_queue.h"

void EventQueue_Initialize(TEventQueue* queue, TEvent* events, uint32_t capacity) {
    queue->events = events;
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
}

bool EventQueue_Enqueue(TEventQueue* queue, TEvent event) {
    if (EventQueue_IsFull(queue)) {
        return false;
    }

    if (queue->front == -1) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->events[queue->rear] = event;
    return true;
}

TEvent EventQueue_Dequeue(TEventQueue* queue) {
    if (EventQueue_IsEmpty(queue)) {
        TEvent emptyEvent = {0, NULL, 0};
        return emptyEvent;
    }

    TEvent event = queue->events[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    return event;
}

TEvent EventQueue_Peek(TEventQueue* queue) {
    if (EventQueue_IsEmpty(queue)) {
        TEvent emptyEvent = {0, NULL, 0};
        return emptyEvent;
    }

    return queue->events[queue->front];
}

bool EventQueue_IsEmpty(TEventQueue* queue) {
    return (queue->front == -1);
}

bool EventQueue_IsFull(TEventQueue* queue) {
    return ((queue->rear + 1) % queue->capacity == queue->front);
}

