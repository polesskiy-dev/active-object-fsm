/**
 * @file fsm.h
 *
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
 *
 * @author apolisskyi
 */

#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <assert.h>

// TODO move it to active-object to implement state traversing
/*
STATE_T##_HANDLE_FUNCTIONS stateHandleFunctionsList[statesMax]\\
 */

/**
 * @def DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax)
 * @brief Declares the basic FSM constructs.
 * @details This macro declares function pointer types, structs, and functions that are essential for a basic FSM.
 *
 * @tparam ACTIVE_OBJECT_T The type of the Active Object using this FSM.
 * @tparam EVENT_T The type representing events.
 * @tparam STATE_T The type representing states.
 * @tparam eventsMax The maximum number of events supported.
 * @tparam statesMax The maximum number of states supported.
 */
#define DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
/* State handler function type */  \
typedef STATE_T (*EVENT_T##_HANDLE_F)(ACTIVE_OBJECT_T *const activeObject, EVENT_T event); \
typedef bool    (*EVENT_T##_GUARD_F)(ACTIVE_OBJECT_T *const activeObject, EVENT_T event);  \
typedef bool    (*STATE_T##_HOOK_F)(ACTIVE_OBJECT_T *const activeObject, void *const ctx);    \
                                                                             \
typedef struct {                                                              \
    STATE_T##_HOOK_F  enter;  \
    STATE_T##_HOOK_F  traverse;    \
    STATE_T##_HOOK_F  exit;   \
} STATE_T##_HOOKS;                                                \
\
STATE_T ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
        ACTIVE_OBJECT_T *const activeObject, \
        EVENT_T event,                                                          \
        EVENT_T##_HANDLE_F transitionTable[statesMax][eventsMax],                \
        STATE_T##_HANDLE_FUNCTIONS stateHandlersList[statesMax]                 \
    );\
bool ACTIVE_OBJECT_T##_FSM_BasicTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState);\
bool ACTIVE_OBJECT_T##_HooksTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState, void *const ctx, STATE_T##_HOOKS statesHooksList[statesMax]);

/**
 * @def DECLARE_GUARD(ACTIVE_OBJECT_T, EVENT_T, CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION)
 * @brief Declares a guard function for a specific condition.
 * @details This macro produces a function that evaluates a condition and calls either an ON_TRUE_FUNCTION or an ON_FALSE_FUNCTION based on the condition's result.
 *
 * @tparam ACTIVE_OBJECT_T The type of the Active Object using this guard.
 * @tparam EVENT_T The type representing events.
 * @tparam CONDITION_FUNCTION The function to evaluate the guard condition.
 * @tparam ON_TRUE_FUNCTION The function to be called if the guard condition evaluates to true.
 * @tparam ON_FALSE_FUNCTION The function to be called if the guard condition evaluates to false.
 * 
 * ### Example:
 * @code
 * // TODO
 * @endcode
 */
#define DECLARE_GUARD(ACTIVE_OBJECT_T, EVENT_T, CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) \
    REQUEST_STATE GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION(ACTIVE_OBJECT_T *const activeObject, EVENT_T event) { \
        if (CONDITION_FUNCTION(activeObject, event)) return ON_TRUE_FUNCTION(activeObject, event);                                             \
                                                                       \
        return ON_FALSE_FUNCTION(activeObject, event);   \
    };

/**
 * @def GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION)
 * @brief Convenience macro to represent a specific guard function.
 * @details This macro simplifies the invocation of the declared guard function based on the provided CONDITION_FUNCTION, ON_TRUE_FUNCTION, and ON_FALSE_FUNCTION.
 * 
 * ### Example:
 * @code
 * // TODO
 * @endcode
 */
#define GUARD(CONDITION_FUNCTION, ON_TRUE_FUNCTION, ON_FALSE_FUNCTION) (GUARD_##CONDITION_FUNCTION##_##ON_TRUE_FUNCTION##_##ON_FALSE_FUNCTION)

/* should never be defined, for documentation purpose only */
#ifdef DOXYGEN_ONLY

/**
 * @brief Invoke state handler f from transitions table by current state and event: [state][event] => f(event)
 *
 * @param activeObject[in,out] - active object object
 * @param event[in] - new event
 * @param transitionTable[in] - event handlers functions 2D array
 * @param stateHandleFunctionsList[in] - state handle functions array
 * @return next state or 0 in case of state handler lack in transitionTable
 */
STATE_T ACTIVE_OBJECT_T_FSM_ProcessEventToNextState(ACTIVE_OBJECT_T *const activeObject, EVENT_T event, EVENT_T_HANDLE_F transitionTable[statesMax][eventsMax])

/**
 * @brief Active Object state transition
 *
 * @param activeObject Pointer to the Active Object
 * @param nextState Next state to transition to
 * 
 * @return whether transition succeed
 *
 * ### Example:
 * @code{.c}
 * MyActiveObjectType myActiveObject;
 * MyStateType nextState = SOME_STATE;
 * 
 * bool result = MyActiveObjectType##_BasicTransitionToNextState(&myActiveObject, nextState);
 * if (result) {
 *     printf("Transition successful!\n");
 * } else {
 *     printf("Transition failed!\n");
 * }
 * @endcode
 */
bool ACTIVE_OBJECT_T_FSM_BasicTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState);

/**
 * @brief Performs a state transition with hooks.
 *
 * This function performs a transition to the given next state, and calls the appropriate hooks
 * based on the transition type (entry, exit, or self-transition).
 *
 * @param activeObject Pointer to the active object.
 * @param nextState The state to transition to.
 * @param ctx Context pointer that could be passed to hooks.
 * @param statesHooksList List of hooks for each state.
 * 
 * @return True if all hooks executed successfully, false otherwise.
 * 
 * ### Example:
 * @code{.c}
 * MyActiveObjectType myActiveObject;
 * MyStateType nextState = SOME_STATE;
 * void *context = NULL; // Replace with actual context if needed
 * MyStateType_HOOKS statesHooksList[MAX_STATES];
 *
 * // Initialize statesHooksList
 * statesHooksList[SOME_STATE].enter = MyEnterHookFunction;
 * statesHooksList[SOME_STATE].exit = MyExitHookFunction;
 * statesHooksList[SOME_STATE].traverse = MyTraverseHookFunction;
 * 
 * bool result = MyActiveObjectType_HooksTransitionToNextState(&myActiveObject, nextState, context, statesHooksList);
 * if (result) {
 *     printf("Transition with hooks successful!\n");
 * } else {
 *     printf("Transition with hooks failed!\n");
 * }
 * @endcode
 */
bool ACTIVE_OBJECT_T_HooksTransitionToNextState(ACTIVE_OBJECT_T *const activeObject, STATE_T nextState, void *const ctx, STATE_T##_HOOKS statesHooksList[statesMax]);

#endif

#endif //FSM_H
