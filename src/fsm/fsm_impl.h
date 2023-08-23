#ifndef FSM_IMPL_H
#define FSM_IMPL_H

#include "./fsm.h"

#define FSM_IMPLEMENTATION(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
                                                                                    \
STATE_T ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
        ACTIVE_OBJECT_T *const activeObject, \
        EVENT_T event,                                                       \
        EVENT_T##_HANDLE_F transitionTable[statesMax][eventsMax],                    \
        STATE_T##_HANDLE_FUNCTIONS stateHandlersList[statesMax]                 \
    ) {                                                                      \
        STATE_T currState = activeObject->state; \
        EVENT_T##_HANDLE_F stateHandler = transitionTable[currState][event.sig];     \
        \
        /* try to avoid lack of state handlers, returns 0 (NO_STATE) */   \
        if(NULL == stateHandler) return (STATE_T){0};        \
                                                                             \
        STATE_T nextState = stateHandler(activeObject, event);                      \
                                                                                    \
        return nextState;                                                    \
    };\

    /* TODO add non basic transition, handle start, traverse, exit state functions */ \
    \
    bool ACTIVE_OBJECT_T##_basicTransitionToNextState(ACTIVE_OBJECT_T *const self, STATE_T nextState) { \
        self->state = nextState; \
        return true; \
    } \    

#endif //FSM_IMPL_H
