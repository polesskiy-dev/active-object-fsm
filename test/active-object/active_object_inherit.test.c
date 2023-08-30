#include "../../libraries/Unity/src/unity.h"
#include "../../src/active_object/active_object.h"

#define QUEUE_MAX_SIZE 8
#define ACTIVE_OBJECT_ID 2

 typedef enum {
    NO_SIG,
    EVENT_SIG_1 = 1,
    EVENT_SIG_2 = 2,
    EVENT_SIG_3 = 3,
    SIG_MAX,
} TEST_EVENT_SIG;

typedef enum {
    NO_STATE,
    STATE_1 = 1,
    STATE_2 = 2,
    STATE_3 = 3,
    STATES_MAX,
} TEST_STATE;

typedef struct TTestEvent {
    TEST_EVENT_SIG sig;
    void* payload;
    size_t size;
} TTestEvent;

/** @extends TActiveObject */
typedef struct {
    TActiveObject super;
    bool additionalField;
} TSubActiveObject;

TState statesList[STATES_MAX] = {   [STATE_1] = {.name = STATE_1, .onEnter = NULL, .onTraverse = NULL, .onExit = NULL},
                                    [STATE_2] = {.name = STATE_2, .onEnter = NULL, .onTraverse = NULL, .onExit = NULL},
                                    [STATE_3] = {.name = STATE_3, .onEnter = NULL, .onTraverse = NULL, .onExit = NULL}};

void TSubActiveObject_Initialize(TSubActiveObject* me, const uint8_t id, TTestEvent* events, uint32_t capacity) {
    ActiveObject_Initialize(&(me->super), id, (TEvent*)events, capacity);
    me->additionalField = false;
}                                   

void setUp(void) {
    // Set up stuff here
}

void tearDown(void) {
    // Clean stuff up here
}

void test_initializeActiveObject(void) {
    TTestEvent events[QUEUE_MAX_SIZE];
    TSubActiveObject subActiveObject;
    TSubActiveObject_Initialize(&subActiveObject, ACTIVE_OBJECT_ID, events, QUEUE_MAX_SIZE);
    
    TEST_ASSERT_EQUAL(ACTIVE_OBJECT_ID, subActiveObject.super.id);
    TEST_ASSERT_TRUE(EventQueue_IsEmpty(&(subActiveObject.super.queue)));
    TEST_ASSERT_NULL(subActiveObject.super.state);
}

void test_dispatchEvent(void) {
    TTestEvent events[QUEUE_MAX_SIZE];
    TSubActiveObject subActiveObject;
    TSubActiveObject_Initialize(&subActiveObject, ACTIVE_OBJECT_ID, events, QUEUE_MAX_SIZE);
    
    ActiveObject_Dispatch(&subActiveObject.super, (TEvent){EVENT_SIG_1, NULL, 0});

    TEST_ASSERT_FALSE(EventQueue_IsEmpty(&subActiveObject.super.queue));
}

void test_processQueue_WithEvent(void) {
    TTestEvent events[QUEUE_MAX_SIZE];
    TSubActiveObject subActiveObject;
    TSubActiveObject_Initialize(&subActiveObject, ACTIVE_OBJECT_ID, events, QUEUE_MAX_SIZE);
    
    ActiveObject_Dispatch(&subActiveObject.super, (TEvent){EVENT_SIG_1, NULL, 0});
    TEvent processedEvent = ActiveObject_ProcessQueue(&subActiveObject.super);
    TEST_ASSERT_EQUAL(EVENT_SIG_1, processedEvent.sig);
}

void test_setActiveObjectState(void) {
    TTestEvent events[QUEUE_MAX_SIZE];
    TSubActiveObject subActiveObject;
    TSubActiveObject_Initialize(&subActiveObject, ACTIVE_OBJECT_ID, events, QUEUE_MAX_SIZE);
    
    subActiveObject.super.state = &statesList[STATE_1];
    
    TEST_ASSERT_EQUAL(subActiveObject.super.state, &statesList[STATE_1]);
    TEST_ASSERT_EQUAL(subActiveObject.super.state->name, statesList[STATE_1].name);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initializeActiveObject);
    RUN_TEST(test_setActiveObjectState);
    RUN_TEST(test_dispatchEvent);
    return UNITY_END();
}