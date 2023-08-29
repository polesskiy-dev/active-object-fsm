#ifndef FSM_IMPL_H
#define FSM_IMPL_H

#include "./fsm.h"

// #define FSM_IMPLEMENTATION(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
//                                                                                     \
// STATE_T ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
//         ACTIVE_OBJECT_T *const activeObject, \
//         EVENT_T event,                                                       \
//         EVENT_T##_HANDLE_F transitionTable[statesMax][eventsMax]                    \
//     ) {                                                                      \
//         STATE_T currState = activeObject->state; \
//         EVENT_T##_HANDLE_F stateHandler = transitionTable[currState][event.sig];     \
//         \
//         /* try to avoid lack of state handlers, returns 0 (NO_STATE) */   \
//         if(NULL == stateHandler) return (STATE_T){0};        \
//                                                                              \
//         STATE_T nextState = stateHandler(activeObject, event);                      \
//                                                                                     \
//         return nextState;                                                    \
//     };\
//     \
//     bool ACTIVE_OBJECT_T##_BasicTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState, void *const ctx) { \
//         activeObject->state = nextState; \
//         return true; \
//     } \
//     \
//     bool ACTIVE_OBJECT_T##_HooksTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState, void *const ctx, STATE_T##_HOOKS statesHooksList[statesMax]) {\
//         bool hooksExecutionResult = false;\
//         /* Next state can't be NULL */\
//         if((STATE_T){0} == nextState) return false;\
//         \
//         STATE_T currState = activeObject->state;\
//         \
//         /* 0 -> nextState: Transition from initial state (NULL state), enter + traverse hooks */\
//         if ((STATE_T){0} == currState) {\
//             if (NULL != statesHooksList[nextState] && NULL != statesHooksList[nextState].enter)\
//                 hooksExecutionResult &= statesHooksList[nextState].enter(activeObject, ctx); \
//             if (NULL != statesHooksList[nextState].traverse)\
//                 hooksExecutionResult &= statesHooksList[nextState].traverse(activeObject, ctx); \
//             \
//             return hooksExecutionResult;\
//         };\
//         \
//         /* currState -> currState: activeObject-transition, run only traverse hook */\
//         if (currState == nextState) {\
//             if (NULL != statesHooksList[currState] && NULL != statesHooksList[currState].traverse) \
//                     return statesHooksList[currState].traverse(activeObject, ctx);\
//         };\
//         /* currState -> nextState: Full scenario, exit, traverse, enter hooks */\
//         if (currState != nextState) {\
//             if (NULL != statesHooksList[currState] && NULL != statesHooksList[currState].exit)\
//                 hooksExecutionResult &= statesHooksList[currState].exit(activeObject, ctx); \
//             if (NULL != statesHooksList[nextState] && NULL != statesHooksList[nextState].enter)\
//                 hooksExecutionResult &= statesHooksList[nextState].enter(activeObject, ctx); \
//             if (NULL != statesHooksList[nextState] && NULL != statesHooksList[nextState].traverse)\
//                 hooksExecutionResult &= statesHooksList[nextState].traverse(activeObject, ctx); \
//         };\
//         return hooksExecutionResult;\
//     }

#endif //FSM_IMPL_H
