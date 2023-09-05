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
 * @details Invoke state handler f from transitions table by current state and event: [currState][event] => f(event): nextState
 *
 * @param[in] activeObject The active object.
 * @param[in] event The incoming event.
 * @param[in] statesMax The maximum number of states.
 * @param[in] eventsMax The maximum number of events.
 * @param[in] statesList The list of states.
 * @param[in] transitionTable The transition table for state-event pairs.
 *
 * @return A pointer to the next state
 * @returns 0 (EMPTY_STATE) in case of state handler lack in transitionTable
 * @returns -1 (INVALID_STATE) in case of invalid input args
 */
const TState *FSM_ProcessEventToNextState(
    TActiveObject *const activeObject,
    TEvent event,
    uint32_t statesMax,
    uint32_t eventsMax,
    const TState statesList[statesMax],
    const TEventHandler transitionTable[statesMax][eventsMax]);

/**
 * @brief Transitions the active object to the next state 
 * @details Invokes state hooks (onEnter, onTraverse, onExit) 
 * of the current and next states appropriately.
 * Returns false on any hook failure (false return).
 *
 * @param[in,out] activeObject The active object.
 * @param[in] nextState The next state to transition to.
 * @param[in] statesMax The maximum number of states.
 * @param[in] statesList The list of states.
 *
 * @return True if the transition is successful, false otherwise.
 */
bool FSM_TraverseNextState(
    TActiveObject *const activeObject,
    const TState *const nextState);    

/** @brief Checks if two states are equal based on their name. */
bool FSM_IsEqualStates(const TState *const stateA, const TState *const stateB);

/** @brief Checks if a state is valid (i.e., not an empty or invalid state). */
bool FSM_IsValidState(const TState *const state);

#define DECLARE_GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION) \
    const TState* GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION(TActiveObject *const activeObject, TEvent event) { \
        if (CONDITION_FUNCTION(activeObject, event)) return ON_TRUE_FUNCTION(activeObject, event); \
        return (const TState*)NULL;   \
    };

#define GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION) (GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION)    

#endif //FSM_H
