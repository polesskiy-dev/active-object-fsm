/**
 * @file fsm.h
 *
 * @brief FSM for Active Object  - A Hybrid of Mealy and Moore State Machines.
 * @see {@link ../../test/fsm/fsm.test.c} for usage examples.
 *
 * @author apolisskyi
 */

#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../active_object/active_object.h"

typedef const TState* (*TEventHandler)(TActiveObject *const activeObject, TEvent event);

/**
 * @brief Processes an incoming event
 * @details Invoke state handler f from transition table by current state and event: [currState][event] => f(event): nextState
 *
 * @param[in] activeObject The active object.
 * @param[in] event The incoming event.
 * @param[in] statesMax The maximum number of states.
 * @param[in] eventsMax The maximum number of events.
 * @param[in] transitionTable The transition table for state-event pairs.
 *
 * @return A pointer to the next state
 * @returns 0 (EMPTY_STATE) in case of state handler lack in transitionTable
 * @returns -1 (INVALID_STATE) in case of invalid input args
 */
const TState *FSM_ProcessEventToNextStateFromTransitionTable(
    TActiveObject *const activeObject, /**< The active object. */
    TEvent event, /**< The incoming event. */
    uint32_t statesMax, /**< The maximum number of states. */
    uint32_t eventsMax, /**< The maximum number of events. */
    const TEventHandler transitionTable[statesMax][eventsMax]); /**< The transition table for state-event. */

/**
 * @brief Transitions the Active Object to the next state
 * @details Invokes state hooks (onEnter, onTraverse, onExit) 
 * of the current and next states appropriately.
 * Returns false on any hook failure (false return).
 *
 * @param[in,out] activeObject The active object.
 * @param[in] nextState The next state to transition to.
 *
 * @return True if the transition is successful, false otherwise.
 */
bool FSM_TraverseAOToNextState(
    TActiveObject *const activeObject,
    const TState *const nextState);    

/** @brief Checks if two states are equal based on their name. */
bool FSM_IsEqualStates(const TState *const stateA, const TState *const stateB);

/** @brief Checks if a state is valid (i.e., not an empty or invalid state). */
bool FSM_IsValidState(const TState *const state);

/**
 * @brief Guard function declaration macro
 * @note should be invoked before using appropriate GUARD macro in transition table
 * @details Creates a guard function for a given condition function and two event handler functions.
 * For true condition result the first event handler function will be called, for false - the second one.
 *
 * ### Example
 * @code
 * TODO make an example
 * @endcode
 */
#define DECLARE_GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) \
    const TState* GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION(TActiveObject *const activeObject, TEvent event) { \
        if (CONDITION_FUNCTION(activeObject, event)) return ON_TRUE_FUNCTION(activeObject, event);  \
        return ON_FALSE_FUNCTION(activeObject, event);  \
        return (const TState*)NULL;   \
    };

/**
 * @brief Guard function macro
 * @note DECLARE_GUARD should be invoked before using appropriate GUARD macro in transition table
 */
#define GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION

#endif //FSM_H
