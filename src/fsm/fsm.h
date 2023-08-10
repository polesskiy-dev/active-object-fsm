/**
 * @file fsm.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief FSM for Active Object  - A Hybrid of Mealy and Moore State Machines.
 *
 * @details This Finite State Machine (FSM) implementation combines the elements of both Mealy and Moore models:
 *
 * - **Moore Machine**: The FSM provides an `enter` function for states. This function is executed as soon as a state is entered,
 *   which is characteristic of Moore machines where outputs (or actions in our case) depend solely on the current state.
 *
 * - **Mealy Machine**: The FSM processes events or inputs using functions like `run`. This behavior is reminiscent of Mealy machines
 *   where outputs (or actions) are dependent on both the current state and the input event.
 *
 * By combining these elements, this FSM offers the flexibility of both models, allowing for actions on both state entry and based on events.
 */

#ifndef FSM_H
#define FSM_H

#include <assert.h>

// TODO move it to active-object to implement state traversing
/*

                                                                             \
STATE_T##_HANDLE_FUNCTIONS stateHandleFunctionsList[statesMax]\\
 */

/**
 * @brief Active Object FSM - A Hybrid of Mealy and Moore State Machines.
 *
 */
#define DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
/**
 * @brief State handler function type
 */\
typedef STATE_T (*EVENT_T##_HANDLE_F)(ACTIVE_OBJECT_T *const activeObject, EVENT_T event); \
typedef bool (*EVENT_T##_GUARD_F)(ACTIVE_OBJECT_T *const activeObject, EVENT_T event);     \
typedef void (*STATE_T##_HANDLE_F)(ACTIVE_OBJECT_T *const activeObject, EVENT_T event);    \
                                                                             \
typedef struct {                                                              \
    STATE_T##_HANDLE_F  enter;  \
    STATE_T##_HANDLE_F  traverse;    \
    STATE_T##_HANDLE_F  exit;   \
} STATE_T##_HANDLE_FUNCTIONS;                                                \
/**
 * @brief Invoke state handler f from transitions table by current state and event: [state][event] => f(event)
 *
 * @param self[in,out] - active object object
 * @param event[in] - new event
 * @param transitionTable[in] - event handlers functions 2D array
 * @param stateHandleFunctionsList[in] - state handle functions array
 * @return next state
 */\
STATE_T ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
        ACTIVE_OBJECT_T *const activeObject, \
        EVENT_T event,                                                       \
        EVENT_T##_HANDLE_F transitionTable[statesMax][eventsMax]             \
    ) {                                                                      \
        STATE_T currState = activeObject->state; \
        EVENT_T##_HANDLE_F stateHandler = transitionTable[currState][event.sig];     \
                                                                             \
        assert(NULL != stateHandler);                                        \
                                                                             \
        STATE_T nextState = stateHandler(activeObject, event);               \
                                                                             \
        return nextState;                                                    \
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
