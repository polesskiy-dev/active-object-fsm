/**
 * @file queue.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief Template Active Object
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdbool.h>

#include "../queue/queue.h"
#include "../fsm/fsm.h"

// TODO should we implement publish/subscribe? So we can have a list of subscriptions inside the object?
//  The main idea here is to resolve a situation when multiple objects consumes same event e.g. from ISR

// TODO it seems that global superloop is kinda "scheduler" and we need there "isIdle" function to sleep on lack of events

// TODO what if same DECLARE_QUEUE invoked twice?

typedef struct {
    uint8_t id;
} ACTIVE_OBJECT_BASE;

void ACTIVE_OBJECT_BASE_Ctor(ACTIVE_OBJECT_BASE *const self, uint8_t id) {
    self->id = id;
}

#define DECLARE_ACTIVE_OBJECT(ACTIVE_OBJECT_T, EVENT_T, STATE_T, id, maxQueueCapacity)                      \
                                                                                                              \
    DECLARE_QUEUE(EVENT_T, maxQueueCapacity)                                                                  \
                                                                                                              \
    typedef struct {                                                                                          \
        ACTIVE_OBJECT_BASE super;                                         \
        QUEUE_##EVENT_T queue;                           \
        STATE_T state;                                   \
    } ACTIVE_OBJECT_T;                                                                                            \
                                                                                                                  \
    /**
    * @brief Event handler callback function type
    */\
    typedef void (*EVENT_T##_HANDLER_F)(ACTIVE_OBJECT_T *const self, EVENT_T event);                              \
                                                                                                                  \
    typedef void (*ACTIVE_OBJECT_T##HAS_EMPTY_QUEUE_F)(ACTIVE_OBJECT_T *const self);  \
                                                                                                              \
    void ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, STATE_T initialState) {                              \
        ACTIVE_OBJECT_BASE_Ctor(&self->super, id); \
        QUEUE_##EVENT_T##_Ctor(&self->queue);                                                                 \
        self->state = initialState;                                                                             \
    };                                                                                                              \
                                                                                                                 \
    void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) {         \
        QUEUE_##EVENT_T##_Enqueue(&self->queue, event);                   \
    };                                                                                                         \
                                                                                                               \
    /**
    * Run it in Tasks()
    * // TODO maybe add arg hasEmptyQueueCb() - to notify that MCU can go to sleep?
    */\
    void ACTIVE_OBJECT_T##_ProcessQueue(ACTIVE_OBJECT_T *const self, EVENT_T##_HANDLER_F eventHandlerCb, ACTIVE_OBJECT_T##HAS_EMPTY_QUEUE_F hasEmptyQueueCb) {                 \
        bool isEmptyQueue = EMPTY_QUEUE == QUEUE_##EVENT_T##_GetSize(&self->queue);                               \
                                                                                                                  \
        if (isEmptyQueue) return hasEmptyQueueCb(self);                                                                \
                                                                                                                  \
        EVENT_T e = QUEUE_##EVENT_T##_Dequeue(&self->queue);  \
        eventHandlerCb(self, e); \
    };

#endif //ACTIVE_OBJECT_H
