#include "../active_object/active_object.h"
#include "./fsm.h"

const TState emptyState = EMPTY_STATE;
const TState invalidState = INVALID_STATE;

inline bool FSM_IsEqualStates(const TState *const stateA, const TState *const stateB) {
    return stateA->name == stateB->name;
};

inline bool FSM_IsValidState(const TState *const state) {
    return EMPTY_STATE.name != state->name && INVALID_STATE.name != state->name;
};

const TState *FSM_ProcessEventToNextStateFromTransitionTable(
        TActiveObject *const activeObject,
        TEvent event,
        uint32_t statesMax,
        uint32_t eventsMax,
        const TEventHandler transitionTable[statesMax][eventsMax]) {

    /* Validate input args */

    // Validate Active object
    if (NULL == activeObject
        || NULL == transitionTable)
        return &invalidState; // Handle null pointers as needed

    const TState *const currState = activeObject->state;

    // Validate current state
    if (currState->name < 0 || currState->name >= statesMax) return &invalidState;

    // Validate current event
    if (event.sig < 0 || event.sig >= eventsMax) return &invalidState;

    // Lookup transition table to find the handler for the current state and event
    const TEventHandler eventHandler = transitionTable[currState->name][event.sig];

    // Call the handler to get the next state and make side effects
    if (eventHandler) {
        const TState *nextState = eventHandler(activeObject, event);

        return nextState;
    }

    // Return empty state if no transition exists
    return &emptyState;
};

// Execute a state hook and return its status.
static bool _executeHook(TStateHook hook, TActiveObject *activeObject) {
    if (hook) {
        return hook(activeObject, NULL);
    }
    return true; // No hook to execute, so consider it successful
}

bool FSM_TraverseAOToNextState(
        TActiveObject *const activeObject,
        const TState *const nextState) {
    // Null args checks
    if (!activeObject || !nextState) {
        return false;
    }

    // Validate next state
    if (!FSM_IsValidState(nextState)) {
        return false;
    }

    const TState *currState = &(*activeObject->state);

    // If the next state is the same as the current state
    if (FSM_IsEqualStates(currState, nextState)) {
        return _executeHook(currState->onTraverse, activeObject);
    }

    // If the next state is different, execute hooks for transitioning
    if (!_executeHook(currState->onExit, activeObject)) {
        return false;
    }

    // Update the state
    activeObject->state = (TState *) nextState;

    if (!_executeHook(activeObject->state->onEnter, activeObject) ||
        !_executeHook(activeObject->state->onTraverse, activeObject)) {
        return false;
    }

    return true;
};
