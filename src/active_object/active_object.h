/**
 * @file active_object.h
 *
 * @brief Active Object Design Pattern Implementation
 * @see events_queue.h for the underlying queue implementation.
 *
 * @details This header file provides the API for implementing an Active Object.
 * The Active Object pattern is used to decouple method execution from 
 * method invocation in concurrent systems. The pattern uses asynchronous
 * messaging to delegate method invocation. It provides
 * a framework for handling complex states through state hooks, as well as 
 * mechanisms for dispatching and processing messages from a queue.
 * Also, the base Active Object struct can be extended (inherited) to provide
 * user-defined functionality.
 * 
 * ### Example:
 * @code
 * // Active Object inheritance
 * typedef enum { NO_STATE, STATE_1 = 1, STATES_MAX } TEST_STATE; // state names
 * typedef enum { NO_SIG, EVENT_SIG_1 = 1, EVENTS_MAX } TEST_EVENT_SIG; // event signals names
 * TEvent events[QUEUE_MAX_SIZE]; // events list for the queue
 * 
 * // sub Active Object
 * typedef struct {
 *      TActiveObject super;
 *      bool additionalField;
 *  } TSubActiveObject;
 * 
 * // states description list
 * TState statesList[STATES_MAX] = { [STATE_1] = {.name = STATE_1, .onEnter = NULL, .onTraverse = NULL, .onExit = NULL} };
 * 
 * // sub Active Object constructor
 * void TSubActiveObject_Initialize(TSubActiveObject* me, const uint8_t id, TEvent* events, uint32_t capacity) {
 *      ActiveObject_Initialize(&(me->super), id, events, capacity);
 *      me->additionalField = false;
 *  }} 
 * @endcode
 *
 * @author apolisskyi
 */

#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "../event_queue/event_queue.h"

/** @brief Macro to create FSM entry point - inittial empty state. */
#define EMPTY_STATE ((TState){.name = 0})

/** @brief Macro to create invalid state indication */
#define INVALID_STATE ((TState){.name = -1})

typedef struct TActiveObject TActiveObject;

/** @brief Function pointer type for state hooks.
 *
 *  @param activeObject Pointer to the active object.
 *  @param ctx Context pointer.
 *  @return A boolean value to indicate hook success or failure result.
 */
typedef bool (*TStateHook)(TActiveObject *const activeObject, void *const ctx);

/** @brief Struct representing a single state of an active object. */
typedef struct {
    int32_t name;
    TStateHook onEnter;
    TStateHook onTraverse;
    TStateHook onExit;
} TState;

/** @brief Struct representing an active object. */
struct TActiveObject {
    uint8_t id;
    const TState *state;
    TEventQueue queue;
};

/** @brief Initialize an active object.
 *  @note The events array must be allocated by the user.
 *
 *  @param me Pointer to the active object.
 *  @param id Object ID.
 *  @param events Pointer to the event array.
 *  @param capacity Capacity of the event queue.
 *
 *  ### Example:
 *  @code
 *  TEvent eventArray[10];
 *  TActiveObject activeObject;
 *  ActiveObject_Initialize(&activeObject, 1, eventArray, 10);
 *  @endcode
 */
void ActiveObject_Initialize(TActiveObject* me, const uint8_t id, TEvent* events, uint32_t capacity);

/** @brief Dispatch an event to the active object.
 *
 *  @param me Pointer to the active object.
 *  @param event The event to be dispatched.
 *
 *  ### Example:
 *  @code
 *  TEvent myEvent = {1, NULL, 0};
 *  ActiveObject_Dispatch(&activeObject, myEvent);
 *  @endcode
 */
void ActiveObject_Dispatch(TActiveObject* me, TEvent event);

/** @brief Process the queue of the active object and return an event.
 *
 *  @param me Pointer to the active object.
 *  @return The next event from the queue.
 *
 *  ### Example:
 *  @code
 *  TEvent nextEvent = ActiveObject_ProcessQueue(&activeObject);
 *  @endcode
 */
TEvent ActiveObject_ProcessQueue(TActiveObject* me);

#endif //ACTIVE_OBJECT_H
