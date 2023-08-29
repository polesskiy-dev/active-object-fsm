/**
 * @file active_object.h
 *
 * @brief Active Object Design Pattern Implementation
 *
 * @details
 * The Active Object design pattern decouples method execution from method invocation.
 * This pattern provides a higher level of concurrency while keeping synchronization
 * simple.
 *
 * This implementation is built upon:
 * - An event-driven model where events are stored in a queue.
 * - A mechanism to dispatch and handle these events.
 * - State management to control the behavior and state transitions of the Active Object.
 *
 * Features:
 * - Uses a queue for event storage, ensuring that events are processed in a First-In-First-Out (FIFO) manner.
 * - Supports user-defined event types, state types, and additional fields - to store particular data.
 * - Provides mechanisms to dispatch events, transition between states, and process the event queue.
 *
 * This file provides the macros, data structures, and function prototypes required
 * to create and operate an Active Object.
 *
 * @see queue.h for the underlying queue implementation.
 *
 * @author apolisskyi
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdbool.h>
#include <stdint.h>

#include "../event_queue/event_queue.h"

// TODO should we implement publish/subscribe? So we can have a list of subscriptions inside the object?
//  The main idea here is to resolve a situation when multiple objects consumes same event e.g. from ISR

// TODO it seems that global superloop is kinda "scheduler" and we need there "isIdle" function to sleep on lack of events

/**
 * @def Active object Template
 *
 * @tparam ACTIVE_OBJECT_T Active Object Type
 * @tparam EVENT_T Event Type
 * @tparam STATE_T State Type
 * @tparam FIELDS_T Active Object field Type
 * @tparam id ID value
 * @tparam maxQueueCapacity Queue capacity value
 *
 * ### Example:
 * @code 
 * DECLARE_ACTIVE_OBJECT(MY_ACTIVE_OBJECT, MY_EVENT, MY_STATE, MY_FIELDS, 16)
 * @endcode
 */
// #define DECLARE_ACTIVE_OBJECT(ACTIVE_OBJECT_T, EVENT_T, STATE_T, FIELDS_T, maxQueueCapacity) \
//     DECLARE_QUEUE(EVENT_T, maxQueueCapacity);                                                \
//                                                                                              \
//     typedef struct { \
//         QUEUE_##EVENT_T queue; \
//         uint8_t id; \
//         STATE_T state; \
//         FIELDS_T fields; \
//     } ACTIVE_OBJECT_T; \
//     \
//     typedef STATE_T (*EVENT_T##_HANDLER_F)(ACTIVE_OBJECT_T *const self, EVENT_T event); \
//     typedef bool (*STATE_T##_TRANSITION_F)(ACTIVE_OBJECT_T *const self, STATE_T state, void* ctx); \
//     \
//     void ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, uint8_t id, STATE_T initialState, FIELDS_T fields); \
//     void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event); \
//     bool ACTIVE_OBJECT_T##_HasEmptyQueue(ACTIVE_OBJECT_T *const self); \
//     void ACTIVE_OBJECT_T##_ProcessQueue(ACTIVE_OBJECT_T *const self, EVENT_T##_HANDLER_F eventHandlerCb, STATE_T##_TRANSITION_F transitionToNextStateCb);

// /**
//  * @struct ACTIVE_OBJECT_T
//  * @brief Struct for defining the Active Object
//  *
//  * @param queue Queue to store events for the Active Object
//  * @param id Base of the Active Object containing ID
//  * @param state Current state of the Active Object
//  * @param fields User-defined fields
//  */

// /* should never be defined, for documentation purpose only */
// #ifdef DOXYGEN_ONLY

// /**
//  * @brief Active Object Constructor
//  *
//  * @param self Pointer to the Active Object
//  * @param initialState Initial state of the Active Object
//  * @param fields User-defined fields
//  *
//  * ### Example:
//  * @code
//  * // Create a new active object:
//  * MY_ACTIVE_OBJECT myObject;
//  * MY_ACTIVE_OBJECT_Ctor(&myObject, 1, initialStateEnum, myFields);
//  * @endcode
//  */
// void ACTIVE_OBJECT_T_Ctor(ACTIVE_OBJECT_T *const self, uint8_t id, STATE_T initialState, FIELDS_T fields)

// /**
//  * @brief Dispatch an event to the Active Object
//  *
//  * @param self Pointer to the Active Object
//  * @param event Event to be dispatched
//  *
//  * ### Example:
//  * @code
//  * // Dispatching an event to the active object:
//  * MY_EVENT myEvent = { .sig=SOME_SIG };
//  * MY_ACTIVE_OBJECT_Dispatch(&myObject, myEvent);
//  * @endcode
// */
// void ACTIVE_OBJECT_T_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event);

// /**
//  * @brief Check Active Object queue empty 
//  * 
//  * @param self Pointer to the Active Object
//  * 
//  * @return is queue empty
//  */
// bool ACTIVE_OBJECT_T_HasEmptyQueue(ACTIVE_OBJECT_T *const self);

// /**
//  * @brief Process the event queue of the Active Object
//  *
//  * @param self Pointer to the Active Object
//  * @param eventHandlerCb Callback to handle queue event, returns next state
//  * @param transitionToNextStateCb Callback to transition to the next state
//  *
//  * ### Example:
//  * @code
//  * // Processing the event queue:
//  * if (!MY_ACTIVE_OBJECT_HasEmptyQueue(&myObject)) MY_ACTIVE_OBJECT_ProcessQueue(&myObject, myEventHandler, myTransitionCb); \
//  * @endcode
//  */
// void ACTIVE_OBJECT_T_ProcessQueue(ACTIVE_OBJECT_T *const self, EVENT_T##_HANDLER_F eventHandlerCb, STATE_T##_TRANSITION_F transitionToNextStateCb)

// #endif

#endif //ACTIVE_OBJECT_H


