//#include "../../libraries/Unity/src/unity.h"
//#include "../../src/fsm/fsm.h"
//#include "../../src/fsm/fsm_impl.h"
//
//typedef struct {
//    int sig;
//} MockEvent;
//
//enum {
//    MOCK_EVENT_A_SIG,
//    MOCK_EVENT_B_SIG,
//    MOCK_EVENT_C_SIG
//};
//
//typedef enum {
//    MOCK_STATE_IDLE,
//    MOCK_STATE_RUNNING,
//    MOCK_STATE_PAUSED
//} MockState;
//
//typedef struct {
//    int value;
//    MockState state;
//} MockActiveObject;
//
//DECLARE_FSM(MockActiveObject, MockEvent, MockState, 3, 3);
//FSM_IMPLEMENTATION(MockActiveObject, MockEvent, MockState, 3, 3);
//
//// Mock state handlers
//MockState mock_idle_handler(MockActiveObject *const ao, MockEvent event) {
//    return MOCK_STATE_RUNNING;
//}
//
//MockState mock_running_handler(MockActiveObject *const ao, MockEvent event) {
//    return MOCK_STATE_PAUSED;
//}
//
//MockState mock_paused_handler(MockActiveObject *const ao, MockEvent event) {
//    return MOCK_STATE_IDLE;
//}
//
//void setUp(void) {
//    // Called before each test case
//}
//
//void tearDown(void) {
//    // Called after each test case
//}
//
//void test_fsm_process_event_to_next_state(void) {
//    MockActiveObject ao = { .value = 10 };
//
//    // Declare and initialize transition table
//    MockEvent_HANDLE_F transitionTable[3][3];
//    transitionTable[MOCK_STATE_IDLE][MOCK_EVENT_A_SIG] = mock_idle_handler;
//    transitionTable[MOCK_STATE_RUNNING][MOCK_EVENT_B_SIG] = mock_running_handler;
//    transitionTable[MOCK_STATE_PAUSED][MOCK_EVENT_C_SIG] = mock_paused_handler;
//
//    // Process MOCK_EVENT_A_SIG while in MOCK_STATE_IDLE -> should transition to MOCK_STATE_RUNNING
//    ao.state = MOCK_STATE_IDLE;
//    MockEvent e = { .sig = MOCK_EVENT_A_SIG };
//    MockState nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e, transitionTable, NULL);
//    TEST_ASSERT_EQUAL(MOCK_STATE_RUNNING, nextState);
//
//    // Process MOCK_EVENT_B_SIG while in MOCK_STATE_RUNNING -> should transition to MOCK_STATE_PAUSED
//    ao.state = MOCK_STATE_RUNNING;
//    e.sig = MOCK_EVENT_B_SIG;
//    nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e, transitionTable, NULL);
//    TEST_ASSERT_EQUAL(MOCK_STATE_PAUSED, nextState);
//
//    // Process MOCK_EVENT_C_SIG while in MOCK_STATE_PAUSED -> should transition to MOCK_STATE_IDLE
//    ao.state = MOCK_STATE_PAUSED;
//    e.sig = MOCK_EVENT_C_SIG;
//    nextState = MockActiveObject_FSM_ProcessEventToNextState(&ao, e, transitionTable, NULL);
//    TEST_ASSERT_EQUAL(MOCK_STATE_IDLE, nextState);
//}
//
//int main(void) {
//    UNITY_BEGIN();
//    RUN_TEST(test_fsm_process_event_to_next_state);
//    UNITY_END();
//
//    return 0;
//}
