/**
 * @file queue.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief Template Active Object
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "../queue/queue.h"
#include "../fsm/fsm.h"

// TODO should we implement publish/subscribe? So we can have a list of subscriptions inside the object?
//  The main idea here is to resolve a situation when multiple objects consumes same event e.g. from ISR

// TODO it seems that global superloop is kinda "scheduler" and we need there "isIdle" function to sleep on lack of events

// TODO what if same DECLARE_QUEUE invoked twice?
#define DECLARE_ACTIVE_OBJECT(ACTIVE_OBJECT_T, EVENT_T, STATE_T, maxQueueCapacity, eventsMax, statesMax)      \
                                                                                                              \
    DECLARE_QUEUE(EVENT_T, maxQueueCapacity)                                                                  \
                                                                                                              \
    typedef struct {                                    \
        QUEUE_##EVENT_T queue;                           \
        STATE_T state;                                   \
    } ACTIVE_OBJECT_T;                                      \
                                                                                                              \
    ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, STATE_T initialState) {                                                             \
        QUEUE_##EVENT_T##_Ctor(&self->queue);                                                                 \
        self->state = initialState;                                                                             \
    }                                                                                                              \
                                                        \
    void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) {         \
        QUEUE_##EVENT_T##_Enqueue(&self->queue, event);                   \
    }
#endif //ACTIVE_OBJECT_H
