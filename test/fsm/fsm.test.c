#include "../../libraries/Unity/src/unity.h"
#include "../../src/active_object/active_object.h"
#include "../../src/fsm/fsm.h"

#define QUEUE_MAX_SIZE 8
#define ACTIVE_OBJECT_ID 1

typedef enum { NO_STATE, EMPTY_HOOKS_ST, SUCCESS_HOOKS_ST, FAILURE_HOOKS_ST, STATES_MAX } STATES_NAMES; // state names
typedef enum { NO_SIG, GO_EMPTY_HOOKS_ST, GO_SUCCESS_HOOKS_ST, GO_FAILURE_HOOKS_ST, EVENTS_MAX } EVENT_SIGS; // events signals names

bool _successHook(void *const activeObject, void *const ctx) { return true; };
bool _failureHook(void *const activeObject, void *const ctx) { return false; };

const TState statesList[STATES_MAX] = { 
    [NO_STATE]          = {.name = NO_STATE},
    [EMPTY_HOOKS_ST]    = {.name = EMPTY_HOOKS_ST, .onEnter = NULL, .onTraverse = NULL, .onExit = NULL},
    [SUCCESS_HOOKS_ST]  = {.name = SUCCESS_HOOKS_ST, .onEnter = _successHook, .onTraverse = _successHook, .onExit = _successHook},
    [FAILURE_HOOKS_ST]  = {.name = FAILURE_HOOKS_ST, .onEnter = _failureHook, .onTraverse = _failureHook, .onExit = _failureHook},
};

const TState* _goToEmmptyHooksState(TActiveObject *const activeObject, TEvent event) { return &statesList[EMPTY_HOOKS_ST]; };
const TState* _goToSuccessHooksState(TActiveObject *const activeObject, TEvent event) { return &statesList[SUCCESS_HOOKS_ST]; };
const TState* _goToFailureHooksState(TActiveObject *const activeObject, TEvent event) { return &statesList[FAILURE_HOOKS_ST]; };

bool _onTrue(TActiveObject *const activeObject, TEvent event) { return true; };

DECLARE_GUARD(_onTrue, _goToFailureHooksState);

const TEventHandler transitionTable[STATES_MAX][EVENTS_MAX] = {
    [NO_STATE]          = { [GO_EMPTY_HOOKS_ST] = _goToEmmptyHooksState },
    [EMPTY_HOOKS_ST]    = { [GO_SUCCESS_HOOKS_ST] = _goToSuccessHooksState },
    [SUCCESS_HOOKS_ST]  = { [GO_FAILURE_HOOKS_ST] = GUARD(_onTrue, _goToFailureHooksState) },
    [FAILURE_HOOKS_ST]  = { [GO_SUCCESS_HOOKS_ST] = _goToSuccessHooksState },
};

TEvent eventArray[QUEUE_MAX_SIZE];
TActiveObject activeObject; // = { .id = 1, .state = &statesList[NO_STATE] };

void setUp(void) {
    ActiveObject_Initialize(&activeObject, ACTIVE_OBJECT_ID, eventArray, QUEUE_MAX_SIZE);
}

void tearDown(void) {
    // This is run after EACH test
}

// NO_STATE -> EMPTY_HOOKS_ST
void test_FSM_TraverseNextState_from_NO_STATE_Successfully(void) {
    activeObject.state = &statesList[NO_STATE];
    
    bool result = FSM_TraverseNextState(&activeObject, &statesList[EMPTY_HOOKS_ST]);
    
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_PTR(&statesList[EMPTY_HOOKS_ST], activeObject.state);
}

// EMPTY_HOOKS_ST -> SUCCESS_HOOKS_ST
void test_FSM_TraverseNextState_EmptyHooks_Should_ReturnTrue(void) {
    activeObject.state = &statesList[EMPTY_HOOKS_ST];
    
    bool result = FSM_TraverseNextState(&activeObject, &statesList[SUCCESS_HOOKS_ST]);
    
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_PTR(&statesList[SUCCESS_HOOKS_ST], activeObject.state);
}

// SUCCESS_HOOKS_ST -> SUCCESS_HOOKS_ST
void test_FSM_TraverseNextState_Self_SuccessHooks_Should_ReturnTrue(void) {
    activeObject.state = &statesList[SUCCESS_HOOKS_ST];
    
    bool result = FSM_TraverseNextState(&activeObject, &statesList[SUCCESS_HOOKS_ST]);
    
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_PTR(&statesList[SUCCESS_HOOKS_ST], activeObject.state);
}

// SUCCESS_HOOKS_ST -> FAILURE_HOOKS_ST (success onExist, failure onEmtry, state changes)
void test_FSM_TraverseNextState_FailureHooks_Should_ReturnFalse(void) {
    activeObject.state = &statesList[SUCCESS_HOOKS_ST];
    
    bool result = FSM_TraverseNextState(&activeObject, &statesList[FAILURE_HOOKS_ST]);
    
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL_PTR(&statesList[FAILURE_HOOKS_ST], activeObject.state);
}

// FAILURE_HOOKS_ST -> SUCCESS_HOOKS_ST (traverse is not conducted) 
void test_FSM_TraverseNextState_from_FailureHooks_Fails(void) {
    activeObject.state = &statesList[FAILURE_HOOKS_ST];
    
    bool result = FSM_TraverseNextState(&activeObject, &statesList[SUCCESS_HOOKS_ST]);
    
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL_PTR(&statesList[FAILURE_HOOKS_ST], activeObject.state);
}

void test_FSM_ProcessEventToNextState_Should_TransitionState(void) {
    activeObject.state = &statesList[EMPTY_HOOKS_ST];
    TEvent event = { .sig = GO_SUCCESS_HOOKS_ST };
    
    const TState *nextState = FSM_ProcessEventToNextState(&activeObject, event, STATES_MAX, EVENTS_MAX, statesList, transitionTable);
    
    TEST_ASSERT_EQUAL_PTR(&statesList[SUCCESS_HOOKS_ST], nextState);
}

void test_FSM_ProcessEventToNextState_Should_NotTransitionState_WithGuard(void) {
    activeObject.state = &statesList[SUCCESS_HOOKS_ST];
    TEvent event = { .sig = GO_FAILURE_HOOKS_ST };
    
    const TState *nextState = FSM_ProcessEventToNextState(&activeObject, event, STATES_MAX, EVENTS_MAX, statesList, transitionTable);
    
    TEST_ASSERT_EQUAL_PTR(&statesList[FAILURE_HOOKS_ST], nextState);
}

int main(void) {
    UNITY_BEGIN();

    // TraverseNextState
    RUN_TEST(test_FSM_TraverseNextState_from_NO_STATE_Successfully);
    RUN_TEST(test_FSM_TraverseNextState_EmptyHooks_Should_ReturnTrue);
    RUN_TEST(test_FSM_TraverseNextState_Self_SuccessHooks_Should_ReturnTrue);
    RUN_TEST(test_FSM_TraverseNextState_FailureHooks_Should_ReturnFalse);
    RUN_TEST(test_FSM_TraverseNextState_from_FailureHooks_Fails);
    
    // ProcessEventToNextState
    RUN_TEST(test_FSM_ProcessEventToNextState_Should_TransitionState);
    RUN_TEST(test_FSM_ProcessEventToNextState_Should_NotTransitionState_WithGuard);
    UNITY_END();
    
    return 0;
}

