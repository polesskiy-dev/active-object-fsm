/**
 * @file queue.h
 *
 * @author apolisskyi
 * @brief Template Active Object
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "queue/queue.h"

// TODO what if same DECLARE_QUEUE invoked twice?
#define DECLARE_ACTIVE_OBJECT(eventT, stateT, maxCapacity)      \
    DECLARE_QUEUE(eventT, maxCapacity)                  \
                                                        \
    typedef struct {                                    \
        QUEUE_##eventT queue;                           \
        stateT state;                                   \
    } AO_##eventT;                                      \
                                                        \
    void AO_##eventT##_Dispatch(AO_##eventT *self, eventT event) {         \
        QUEUE_##eventT##_Enqueue(&self->queue, event);                   \
    }
#endif //ACTIVE_OBJECT_H
