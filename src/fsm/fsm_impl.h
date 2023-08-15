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
        assert(NULL != stateHandler);                                        \
                                                                             \
        STATE_T nextState = stateHandler(activeObject, event);                      \
                                                                                    \
        return nextState;                                                    \
    };

#endif //FSM_IMPL_H
