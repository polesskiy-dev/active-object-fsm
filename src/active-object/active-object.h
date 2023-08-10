/**
 * @file active-object.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief Template Active Object
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdbool.h>
#include <stdint.h>

#include "../queue/queue.h"

// TODO should we implement publish/subscribe? So we can have a list of subscriptions inside the object?
//  The main idea here is to resolve a situation when multiple objects consumes same event e.g. from ISR

// TODO it seems that global superloop is kinda "scheduler" and we need there "isIdle" function to sleep on lack of events

// TODO what if same DECLARE_QUEUE invoked twice?

/**
 * @def ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, STATE_T initialState, FIELDS_T fields)
 *
 * @brief Active Object constructor
 *
 * @param self Active Object
 * @param initialState initial state
 * @param fields User-defined fields, accommodates actual application data
 */

/**
 * @brief Active object Template
 *
 * @param ACTIVE_OBJECT_T Active Object Type
 * @param EVENT_T Event Type
 * @param STATE_T State Type
 * @param FIELDS_T Active Object field Type
 * @param id ID value
 * @param maxQueueCapacity Queue capacity value
 */
#define DECLARE_ACTIVE_OBJECT(ACTIVE_OBJECT_T, EVENT_T, STATE_T, FIELDS_T, maxQueueCapacity)             \
                                                                                                             \
    DECLARE_QUEUE(EVENT_T, maxQueueCapacity);                                                                \
                                                                                                             \
    /**
     * @brief Struct for defining the Active Object
     *
     * @param super Base of the Active Object containing ID
     * @param queue Queue to store events for the Active Object
     * @param state Current state of the Active Object
     * @param fields User-defined fields to store additional information
     */\
    typedef struct {                                                                                        \
        QUEUE_##EVENT_T queue;                                                                           \
        uint8_t id;                                                                                         \
        STATE_T state;                                                                                      \
        FIELDS_T fields;                                                                                     \
    } ACTIVE_OBJECT_T;                                                                                       \
                                                                                                             \
                                                                                                             \
    typedef STATE_T (*EVENT_T##_HANDLER_F)(ACTIVE_OBJECT_T *const self, EVENT_T event);\
    typedef void (*ACTIVE_OBJECT_T##HAS_EMPTY_QUEUE_F)(ACTIVE_OBJECT_T *const self);                         \
    typedef bool (*STATE_T##_TRANSITION_F)(ACTIVE_OBJECT_T *const self, STATE_T state);             \
    /**
     * @brief Constructor for Active Object
     *
     * @param self Pointer to the Active Object
     * @param initialState Initial state of the Active Object
     * @param fields User-defined fields
     */                                                                                                     \
    void ACTIVE_OBJECT_T##_Ctor(ACTIVE_OBJECT_T *const self, uint8_t id, STATE_T initialState, FIELDS_T fields) {        \
        QUEUE_##EVENT_T##_Ctor(&self->queue);                                                               \
        self->id = id;                                                                         \
        self->state = initialState;                                                                         \
        self->fields = fields;                                                                              \
    };                                                                                                      \
                                                                                                             \
    /**
     * @brief Dispatch an event to the Active Object
     *
     * @param self Pointer to the Active Object
     * @param event Event to be dispatched
     */                                                                                                     \
    void ACTIVE_OBJECT_T##_Dispatch(ACTIVE_OBJECT_T *const self, EVENT_T event) {                            \
        /*if (QUEUE_##EVENT_T##_IsFull(&self->queue)) return;*/ /* Handle error, e.g., logging */               \
        QUEUE_##EVENT_T##_Enqueue(&self->queue, event);                                                     \
    };                                                                                                      \
                                                                                                             \
    /**
     * @brief Transition to the next state of the Active Object
     *
     * @param self Pointer to the Active Object
     * @param nextState Next state to transition to
     *
     * TODO should be improved, temporary inline, handle here exit -> enter -> traverse for states, implementing Mealy&Moore Hybrid FSM
     */                                                                                                     \
     bool ACTIVE_OBJECT_T##_basicTransitionToNextState(ACTIVE_OBJECT_T *const self, STATE_T nextState) {    \
        self->state = nextState;                                                                             \
        return true; \
    };                                                                                                      \
                                                                                                             \
    /**
     * @brief Process the event queue of the Active Object
     *
     * @param self Pointer to the Active Object
     * @param eventHandlerCb Callback to handle queue event, returns next state
     * @param hasEmptyQueueCb Callback to handle empty queue
     */                                                                                                     \
    void ACTIVE_OBJECT_T##_ProcessQueue(ACTIVE_OBJECT_T *const self, EVENT_T##_HANDLER_F eventHandlerCb, STATE_T##_TRANSITION_F transitionToNextStateCb, ACTIVE_OBJECT_T##HAS_EMPTY_QUEUE_F hasEmptyQueueCb) { \
        bool isEmptyQueue = EMPTY_QUEUE == QUEUE_##EVENT_T##_GetSize(&self->queue);                          \
                                                                                                             \
        if (isEmptyQueue) return hasEmptyQueueCb(self);                                                     \
                                                                                                             \
        EVENT_T e = QUEUE_##EVENT_T##_Dequeue(&self->queue);                                                \
        STATE_T nextState = eventHandlerCb(self, e);                                                        \
        transitionToNextStateCb(self, nextState);                                            \
    };\

#endif //ACTIVE_OBJECT_H
