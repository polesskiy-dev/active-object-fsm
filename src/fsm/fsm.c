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

const TState *FSM_ProcessEventToNextState(
    TActiveObject *const activeObject,
    TEvent event,
    uint32_t statesMax,
    uint32_t eventsMax,
    const TState statesList[statesMax],
    const TEventHandler transitionTable[statesMax][eventsMax]) {

    /* Validate input args */    

    // Validate Active object
    if (NULL == activeObject 
        || NULL == statesList 
        || NULL == transitionTable) return &invalidState; // Handle null pointers as needed

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

bool FSM_TraverseNextState(
    TActiveObject *const activeObject,
    const TState *const nextState) {

    // Null args checks        
    if (NULL == activeObject 
        || NULL == nextState) {
        return false;
    };

    // Validate next state
    if (!FSM_IsValidState(nextState)) {
        return false;
    };

    // Call onExit of current state, if any
    if (NULL != activeObject->state->onExit) {
        bool isSuccessfulHook = activeObject->state->onExit(activeObject, NULL);
        if (!isSuccessfulHook) {
            return false; // Hook failed
        }
    }

    // Update the state
    activeObject->state = (TState *)nextState;

    // Call onEnter of next state, if any
    if (activeObject->state->onEnter) {
        bool isSuccessfulHook = activeObject->state->onEnter(activeObject, NULL);
        if (!isSuccessfulHook) {
            return false; // Hook failed
        }
    }

    // Finally, call onTraverse of next state, if any
    if (activeObject->state->onTraverse) {
        bool isSuccessfulHook = activeObject->state->onTraverse(activeObject, NULL);
        if (!isSuccessfulHook) {
            return false; // Hook failed
        }
    }

    return true;
};
