#ifndef ACTIVE_OBJECT_IMPL_H
#define ACTIVE_OBJECT_IMPL_H

#include "./active_object.h"
#include "../queue/queue_impl.h"

#define ACTIVE_OBJECT_IMPLEMENTATION(ACTIVE_OBJECT_T, EVENT_T, STATE_T, FIELDS_T, maxQueueCapacity) \
    QUEUE_IMPLEMENTATION(EVENT_T, maxQueueCapacity); \
    \
    void ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, uint8_t id, STATE_T initialState, FIELDS_T fields) { \
        QUEUE_##EVENT_T##_Ctor(&self->queue); \
        self->id = id; \
        self->state = initialState; \
        self->fields = fields; \
    } \
    \
    void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) { \
        if (QUEUE_##EVENT_T##_IsFull(&self->queue)) return; /* TODO Handle error, e.g., logging */ \
        QUEUE_##EVENT_T##_Enqueue(&self->queue, event); \
    }                                                                                               \
                                                                                                    \
    /* TODO add non basic transition, handle start, traverse, exit state functions */ \
    \
    bool ACTIVE_OBJECT_T##_basicTransitionToNextState(ACTIVE_OBJECT_T *const self, STATE_T nextState) { \
        self->state = nextState; \
        return true; \
    } \
    \
    void ACTIVE_OBJECT_T##_ProcessQueue(                                                            \
            ACTIVE_OBJECT_T *const self,                                \
            EVENT_T##_HANDLER_F eventHandlerCb,                                                             \
            STATE_T##_TRANSITION_F transitionToNextStateCb,                                                 \
            ACTIVE_OBJECT_T##HAS_EMPTY_QUEUE_F hasEmptyQueueCb) { \
        bool isEmptyQueue = EMPTY_QUEUE == QUEUE_##EVENT_T##_GetSize(&self->queue); \
        if (isEmptyQueue) return hasEmptyQueueCb(self); \
        EVENT_T e = QUEUE_##EVENT_T##_Dequeue(&self->queue); \
        STATE_T nextState = eventHandlerCb(self, e); \
        transitionToNextStateCb(self, nextState); \
    }

#endif //ACTIVE_OBJECT_IMPL_H
