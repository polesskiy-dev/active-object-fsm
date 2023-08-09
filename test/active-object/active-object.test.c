#include "stdint.h"

#include "../../libraries/Unity/src/unity.h"
#include "../../src/active-object/active-object.h"

typedef enum {
    STATE_INIT,
    STATE_ONE,
    STATE_TWO
} State;

typedef enum {
    EVENT_NONE,
    EVENT_START,
    EVENT_STOP
} Event;

DECLARE_ACTIVE_OBJECT(MyActiveObject, Event, State, int, 1, 10);

// Event handler callback for testing
static State MyEventHandler(MyActiveObject *const self, Event event) {
    switch(event) {
        case EVENT_START:
            return STATE_ONE;
        case EVENT_STOP:
            return STATE_TWO;
        default:
            return self->state;
    }
}

// Empty queue callback for testing
static void MyEmptyQueueHandler(MyActiveObject *const self) {
    // Do nothing
}

void setUp(void) {
    // This is run before EACH test
}

void tearDown(void) {
    // This is run after EACH test
}

void test_active_object_initialization(void) {
    MyActiveObject obj;
    MyActiveObject_Ctor(&obj, STATE_INIT, 0);
    TEST_ASSERT_EQUAL(STATE_INIT, obj.state);
}

void test_active_object_dispatch(void) {
    MyActiveObject obj;
    MyActiveObject_Ctor(&obj, STATE_INIT, 0);
    MyActiveObject_Dispatch(&obj, EVENT_START);
    TEST_ASSERT_EQUAL(1, QUEUE_Event_GetSize(&obj.queue));
}

void test_active_object_process_queue(void) {
    MyActiveObject obj;
    MyActiveObject_Ctor(&obj, STATE_INIT, 0);
    MyActiveObject_Dispatch(&obj, EVENT_START);
    MyActiveObject_ProcessQueue(&obj, MyEventHandler, MyEmptyQueueHandler);
    TEST_ASSERT_EQUAL(STATE_ONE, obj.state);
    TEST_ASSERT_EQUAL(0, QUEUE_Event_GetSize(&obj.queue));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_active_object_initialization);
    RUN_TEST(test_active_object_dispatch);
    RUN_TEST(test_active_object_process_queue);
    return UNITY_END();
}

