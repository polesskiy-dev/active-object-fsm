#include "../../libraries/Unity/src/unity.h"
#include "../../src/active-object/active_object.h"
#include "../../src/active-object/active_object_impl.h"

// Define the types for our test
typedef enum {
    TEST_EVENT_A,
    TEST_EVENT_B
} TestEvent;

typedef enum {
    TEST_STATE_IDLE,
    TEST_STATE_RUNNING,
    TEST_STATE_PAUSED
} TestState;

typedef struct {
    int value;
} TestFields;

DECLARE_ACTIVE_OBJECT(TestActiveObject, TestEvent, TestState, TestFields, 5);
ACTIVE_OBJECT_IMPLEMENTATION(TestActiveObject, TestEvent, TestState, TestFields, 5);

TestState handleEvent(TestActiveObject *self, TestEvent e) {
    switch(e) {
        case TEST_EVENT_A: return TEST_STATE_RUNNING;
        case TEST_EVENT_B: return TEST_STATE_PAUSED;
        default: return self->state; // No change in state
    }
}

bool transitionToState(TestActiveObject *self, TestState nextState) {
    return TestActiveObject_basicTransitionToNextState(self, nextState);
}

void handleEmptyQueue(TestActiveObject *self) {
    // For this test, do nothing when the queue is empty.
}

void setUp(void) {
    // Called before each test case
}

void tearDown(void) {
    // Called after each test case
}

void test_constructor(void) {
    TestActiveObject obj;
    TestFields fields = { .value = 10 };
    TestActiveObject_Ctor(&obj, 1, TEST_STATE_IDLE, fields);
    TEST_ASSERT_EQUAL(1, obj.id);
    TEST_ASSERT_EQUAL(TEST_STATE_IDLE, obj.state);
    TEST_ASSERT_EQUAL(10, obj.fields.value);
    TEST_ASSERT_EQUAL(0, QUEUE_TestEvent_GetSize(&obj.queue));
}

void test_dispatchAndProcessQueue(void) {
    TestActiveObject obj;
    TestFields fields = { .value = 10 };
    TestActiveObject_Ctor(&obj, 1, TEST_STATE_IDLE, fields);

    // Dispatch TEST_EVENT_A and process it
    TestActiveObject_Dispatch(&obj, TEST_EVENT_A);
    TestActiveObject_ProcessQueue(&obj, handleEvent, transitionToState, handleEmptyQueue);

    TEST_ASSERT_EQUAL(TEST_STATE_RUNNING, obj.state);

    // Dispatch TEST_EVENT_B and process it
    TestActiveObject_Dispatch(&obj, TEST_EVENT_B);
    TestActiveObject_ProcessQueue(&obj, handleEvent, transitionToState, handleEmptyQueue);

    TEST_ASSERT_EQUAL(TEST_STATE_PAUSED, obj.state);
}

void test_basicTransitionToNextState(void) {
    TestActiveObject obj;
    TestFields fields = { .value = 10 };
    TestActiveObject_Ctor(&obj, 1, TEST_STATE_IDLE, fields);

    // Assert initial state
    TEST_ASSERT_EQUAL(TEST_STATE_IDLE, obj.state);

    // Test transitioning to TEST_STATE_RUNNING
    bool transitioned = TestActiveObject_basicTransitionToNextState(&obj, TEST_STATE_RUNNING);
    TEST_ASSERT_TRUE(transitioned);
    TEST_ASSERT_EQUAL(TEST_STATE_RUNNING, obj.state);

    // Test transitioning to TEST_STATE_PAUSED
    transitioned = TestActiveObject_basicTransitionToNextState(&obj, TEST_STATE_PAUSED);
    TEST_ASSERT_TRUE(transitioned);
    TEST_ASSERT_EQUAL(TEST_STATE_PAUSED, obj.state);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_constructor);
    RUN_TEST(test_dispatchAndProcessQueue);
    RUN_TEST(test_basicTransitionToNextState);
    UNITY_END();

    return 0;
}
