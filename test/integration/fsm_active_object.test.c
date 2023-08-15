#include "../../libraries/Unity/src/unity.h"
#include "../../src/active-object/active_object.h"
#include "../../src/active-object/active_object_impl.h"
#include "../../src/fsm/fsm.h"
#include "../../src/fsm/fsm_impl.h"

#define QUEUE_CAPACITY 5
#define EVENTS_MAX 3
#define STATES_MAX 3

typedef enum {
    MOCK_EVENT_A_SIG,
    MOCK_EVENT_B_SIG,
    MOCK_EVENT_C_SIG
} MockEventSignal;

typedef struct {
    MockEventSignal sig;
} MockEvent;

typedef enum {
    MOCK_STATE_IDLE,
    MOCK_STATE_RUNNING,
    MOCK_STATE_PAUSED
} MockState;

typedef struct {
    int value;
} MockFields;

DECLARE_ACTIVE_OBJECT(MockActiveObject, MockEvent, MockState, MockFields, QUEUE_CAPACITY);
ACTIVE_OBJECT_IMPLEMENTATION(MockActiveObject, MockEvent, MockState, MockFields, QUEUE_CAPACITY);
DECLARE_FSM(MockActiveObject, MockEvent, MockState, EVENTS_MAX, STATES_MAX);
FSM_IMPLEMENTATION(MockActiveObject, MockEvent, MockState, EVENTS_MAX, STATES_MAX);

// Mock state handlers (FSM)
MockState mock_idle_handler(MockActiveObject *const ao, MockEvent event) {
    return MOCK_STATE_RUNNING;
}

MockState mock_running_handler(MockActiveObject *const ao, MockEvent event) {
    return MOCK_STATE_PAUSED;
}

MockState mock_paused_handler(MockActiveObject *const ao, MockEvent event) {
    return MOCK_STATE_IDLE;
}

MockEvent_HANDLE_F stateTransitionTable[STATES_MAX][EVENTS_MAX] = {
        [MOCK_STATE_IDLE] = {
                [MOCK_EVENT_A_SIG] = mock_idle_handler,
                [MOCK_EVENT_B_SIG] = NULL,
                [MOCK_EVENT_C_SIG] = NULL
        },
        [MOCK_STATE_RUNNING] = {
                [MOCK_EVENT_A_SIG] = NULL,
                [MOCK_EVENT_B_SIG] = mock_running_handler,
                [MOCK_EVENT_C_SIG] = NULL
        },
        [MOCK_STATE_PAUSED] = {
                [MOCK_EVENT_A_SIG] = NULL,
                [MOCK_EVENT_B_SIG] = NULL,
                [MOCK_EVENT_C_SIG] = mock_paused_handler
        }
};

void setUp(void) {
    // Called before each test case
}

void tearDown(void) {
    // Called after each test case
}

void integration_test_active_object_with_fsm_and_queue(void) {
    MockActiveObject ao;
    MockFields fields = { .value = 10 };

    // Initialization
    MockActiveObject_Ctor(&ao, 1, MOCK_STATE_IDLE, fields);
    TEST_ASSERT_EQUAL(1, ao.id);
    TEST_ASSERT_EQUAL(MOCK_STATE_IDLE, ao.state);
    TEST_ASSERT_EQUAL(10, ao.fields.value);
    TEST_ASSERT_EQUAL(0, QUEUE_MockEvent_GetSize(&ao.queue));

    // Dispatching and processing an event
    MockEvent e1 = { .sig = MOCK_EVENT_A_SIG };
    MockActiveObject_Dispatch(&ao, e1);
    TEST_ASSERT_EQUAL(1, QUEUE_MockEvent_GetSize(&ao.queue));

    // Process Event with FSM
    MockState nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e1, stateTransitionTable, NULL);
    TEST_ASSERT_EQUAL(MOCK_STATE_RUNNING, nextState);
    ao.state = nextState;  // Update the actual state of the active object

    // Dispatching and processing a second event
    MockEvent e2 = { .sig = MOCK_EVENT_B_SIG };
    MockActiveObject_Dispatch(&ao, e2);
    nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e2, stateTransitionTable, NULL);
    TEST_ASSERT_EQUAL(MOCK_STATE_PAUSED, nextState);
    ao.state = nextState;  // Update the actual state of the active object

    // Dispatching and processing a third event
    MockEvent e3 = { .sig = MOCK_EVENT_C_SIG };
    MockActiveObject_Dispatch(&ao, e3);
    nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e3, stateTransitionTable, NULL);
    TEST_ASSERT_EQUAL(MOCK_STATE_IDLE, nextState);
    ao.state = nextState;  // Update the actual state of the active object
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(integration_test_active_object_with_fsm_and_queue);
    UNITY_END();

    return 0;
}
