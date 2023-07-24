/**
 * @file queue.h
 *
 * @author apolisskyi
 * @brief Template Active Object
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "queue/queue.h"
#include "fsm/fsm.h"

// TODO what if same DECLARE_QUEUE invoked twice?
#define DECLARE_ACTIVE_OBJECT(ACTIVE_OBJECT_T, EVENT_T, STATE_T, maxQueueCapacity, eventsMax, statesMax)      \
    DECLARE_QUEUE(EVENT_T, maxQueueCapacity)                                            \
    DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax)    \
                                                        \
    typedef struct {                                    \
        QUEUE_##EVENT_T queue;                           \
        STATE_T state;                                   \
    } ACTIVE_OBJECT_T;                                      \
                                                        \
    void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) {         \
        QUEUE_##EVENT_T##_Enqueue(&self->queue, event);                   \
    }
#endif //ACTIVE_OBJECT_H
