#include "../../libraries/Unity/src/unity.h"
#include "../../src/active_object/active_object.h"

#define QUEUE_MAX_SIZE 8
#define ACTIVE_OBJECT_ID 1

typedef enum { NO_STATE, STATE_1 = 1, STATES_MAX } TEST_STATE; // state names
typedef enum { NO_SIG, EVENT_SIG_1 = 1, EVENTS_MAX } TEST_EVENT_SIG; // event signals names

void setUp(void) {
    // Set up stuff here
}

void tearDown(void) {
    // Clean stuff up here
}

void test_initializeActiveObject(void) {
    TEvent eventArray[QUEUE_MAX_SIZE];
    TActiveObject activeObject;
    ActiveObject_Initialize(&activeObject, ACTIVE_OBJECT_ID, eventArray, QUEUE_MAX_SIZE);
    
    TEST_ASSERT_EQUAL(ACTIVE_OBJECT_ID, activeObject.id);
    TEST_ASSERT_TRUE(EventQueue_IsEmpty(&activeObject.queue));
    TEST_ASSERT_NULL(activeObject.state);
}

void test_dispatchEvent(void) {
    TEvent eventArray[QUEUE_MAX_SIZE];
    TActiveObject activeObject;
    TEvent testEvent = {EVENT_SIG_1, NULL, 0};
    ActiveObject_Initialize(&activeObject, ACTIVE_OBJECT_ID, eventArray, QUEUE_MAX_SIZE);
    
    ActiveObject_Dispatch(&activeObject, testEvent);
    TEST_ASSERT_FALSE(EventQueue_IsEmpty(&activeObject.queue));
}

void test_processQueue_WithEvent(void) {
    TEvent eventArray[QUEUE_MAX_SIZE];
    TActiveObject activeObject;
    TEvent testEvent = {EVENT_SIG_1, NULL, 0};
    ActiveObject_Initialize(&activeObject, ACTIVE_OBJECT_ID, eventArray, QUEUE_MAX_SIZE);
    
    ActiveObject_Dispatch(&activeObject, testEvent);
    TEvent processedEvent = ActiveObject_ProcessQueue(&activeObject);
    TEST_ASSERT_EQUAL(testEvent.sig, processedEvent.sig);
}

void test_processQueue_EmptyQueue(void) {
    TEvent eventArray[QUEUE_MAX_SIZE];
    TActiveObject activeObject;
    ActiveObject_Initialize(&activeObject, ACTIVE_OBJECT_ID, eventArray, QUEUE_MAX_SIZE);
    
    TEvent processedEvent = ActiveObject_ProcessQueue(&activeObject);
    TEST_ASSERT_EQUAL(NO_SIG, processedEvent.sig);
    TEST_ASSERT_NULL(processedEvent.payload);
    TEST_ASSERT_EQUAL(NO_SIG, processedEvent.size);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initializeActiveObject);
    RUN_TEST(test_dispatchEvent);
    RUN_TEST(test_processQueue_WithEvent);
    RUN_TEST(test_processQueue_EmptyQueue);
    return UNITY_END();
}


