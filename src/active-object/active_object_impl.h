#ifndef ACTIVE_OBJECT_IMPL_H
#define ACTIVE_OBJECT_IMPL_H

#include "./active_object.h"

//Generate Unit tests for this macro on Unity framework
// #define ACTIVE_OBJECT_IMPLEMENTATION(ACTIVE_OBJECT_T, EVENT_T, STATE_T, FIELDS_T, maxQueueCapacity) \
//     QUEUE_IMPLEMENTATION(EVENT_T, maxQueueCapacity); \
//     \
//     void ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, uint8_t id, STATE_T initialState, FIELDS_T fields) { \
//         QUEUE_##EVENT_T##_Ctor(&self->queue); \
//         self->id = id; \
//         self->state = initialState; \
//         self->fields = fields; \
//     } \
//     \
//     void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) { \
//         if (QUEUE_##EVENT_T##_IsFull(&self->queue)) return; /* TODO Handle error, e.g., logging */ \
//         QUEUE_##EVENT_T##_Enqueue(&self->queue, event); \
//     }                                                                                               \
//     \
//     bool ACTIVE_OBJECT_T##_HasEmptyQueue(ACTIVE_OBJECT_T *const self) {\
//         return EMPTY_QUEUE == QUEUE_##EVENT_T##_GetSize(&self->queue); \
//     }\
//     \
//     void ACTIVE_OBJECT_T##_ProcessQueue(\
//             ACTIVE_OBJECT_T *const self, \
//             EVENT_T##_HANDLER_F eventHandlerCb,\
//             STATE_T##_TRANSITION_F transitionToNextStateCb) { \
//         /* TODO debug log it, just double check to no dequeue empty queue */ \
//         if (ACTIVE_OBJECT_T##_HasEmptyQueue(self)) return; \
//         \
//         EVENT_T e = QUEUE_##EVENT_T##_Dequeue(&self->queue); \
//         STATE_T nextState = eventHandlerCb(self, e); \
//         /* TODO implement passing ctx from event */\
//         transitionToNextStateCb(self, nextState, NULL); \
//     }

#endif //ACTIVE_OBJECT_IMPL_H
