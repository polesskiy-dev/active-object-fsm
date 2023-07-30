/**
 * @file fsm.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief Template Finite State Machine
 */

#ifndef FSM_H
#define FSM_H

#include <assert.h>

// TODO for HSM add to STATE struct pointers: to Parent and to Child Nodes, Level from top level state

#define DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
/**
 * @brief State handler function type
 */\
typedef STATE_T (*STATE_T##_HANDLE_F)(ACTIVE_OBJECT_T *activeObject, EVENT_T event); \
typedef bool (*STATE_T##_GUARD_F)(ACTIVE_OBJECT_T *activeObject, EVENT_T event);     \
                                                                             \
typedef struct {                                                              \
    STATE_T##_HANDLE_F  run;    \
    STATE_T##_HANDLE_F  enter;  \
    STATE_T##_HANDLE_F  exit;   \
} STATE_T##_STATE;                                                        \
\
/**
 * @brief Invoke state handler f from transitions table by current state and event: [state][event] => f(event)
 *
 * @param self[in,out] - active object object
 * @param event[in] - new event
 * @param transitionTable[in] - state handlers functions 2D array
 * @return next state
 */\
STATE_T ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
        ACTIVE_OBJECT_T *const activeObject, \
        EVENT_T event, \
        STATE_T##_HANDLE_F transitionTable[statesMax][eventsMax] \
    ) {                                                                       \
        STATE_T currState = activeObject->state; \
        STATE_T##_HANDLE_F stateHandler = transitionTable[currState][event.sig];     \
        assert(NULL != stateHandler);                                       \
        STATE_T nextState = stateHandler(activeObject, event);                \
        return nextState;                                                       \
    };                                                                       \


// Kinda complicated Guard approach, think hot to simplify or just don't use it
#define DECLARE_GUARD(ACTIVE_OBJECT_T, EVENT_T, CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) \
    REQUEST_STATE GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION(ACTIVE_OBJECT_T *const activeObject, EVENT_T event) { \
        if (CONDITION_FUNCTION(activeObject, event)) return ON_TRUE_FUNCTION(activeObject, event);                                             \
                                                                       \
        return ON_FALSE_FUNCTION(activeObject, event);   \
    };

#define GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) (GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION)

#endif //FSM_H
