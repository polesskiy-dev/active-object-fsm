/**
 * @file fsm.h
 *
 * @version 0.0.1
 * @author apolisskyi
 * @brief Template Finite State Machine
 */

#ifndef FSM_H
#define FSM_H

// TODO for HSM add to STATE struct pointers: to Parent and to Child Nodes, Level from top level state

#define DECLARE_FSM(ACTIVE_OBJECT_T, EVENT_T, STATE_T, eventsMax, statesMax) \
\
/**
 * @brief State handler function type
 */\
typedef void (*STATE_T##_HANDLE_F)(ACTIVE_OBJECT_T *self, EVENT_T event); \
                                                                             \
typedef struct {                                                             \
    STATE_T##_HANDLE_F run  \
    STATE_T##_HANDLE_F enter  \
    STATE_T##_HANDLE_F exit  \
} STATE_T##_STATE                                                        \
\
/**
 * @brief Invoke state handler f from transitions table by current state and event: [state][event] => f(event)
 *
 * @param self[in,out] - active object object
 * @param event[in] - new event
 * @param transitionTable[in] - state handlers functions 2D array
 */\
void ACTIVE_OBJECT_T##_FSM_ProcessEventToNextState(\
        ACTIVE_OBJECT_T *const activeObject, \
        EVENT_T event, \
        STATE_T##_HANDLE_F *const transitionTable[statesMax][eventsMax] \
    );

#endif //FSM_H
