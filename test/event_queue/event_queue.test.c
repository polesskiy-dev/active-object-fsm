#define QUEUE_MAX_CAPACITY  (16)

#include "../../libraries/Unity/src/unity.h"
#include "../../src/event_queue/event_queue.h"

typedef enum {
    TEST_SIG_1 = 1,
    TEST_SIG_2 = 2,
    TEST_SIG_3 = 3,
} TEST_SIG;

typedef struct {
    TEST_SIG sig;
    void* payload;
    size_t size;
} TTestEvent;

TTestEvent events[QUEUE_MAX_CAPACITY];
TEventQueue queue;

void setUp(void) {
    EventQueue_Initialize(&queue, (TEvent*)&events, QUEUE_MAX_CAPACITY);
}

void tearDown(void) {
    // Nothing to tear down in this case
}

void test_EventQueue_Initialize(void) {
    TEST_ASSERT_EQUAL_INT(-1, queue.front);
    TEST_ASSERT_EQUAL_INT(-1, queue.rear);
}

void test_EventQueue_Enqueue(void) {
    TEvent event = {TEST_SIG_1, NULL, 0};
    bool enqueueResult = EventQueue_Enqueue(&queue, event);

    TEST_ASSERT_TRUE(enqueueResult);
    TEST_ASSERT_FALSE(EventQueue_IsEmpty(&queue));
}

void test_EventQueue_Dequeue(void) {
    TEvent event = {TEST_SIG_1, NULL, 0};
    EventQueue_Enqueue(&queue, event);

    TEvent dequeuedEvent = EventQueue_Dequeue(&queue);

    TEST_ASSERT_EQUAL_INT(1, dequeuedEvent.sig);
    TEST_ASSERT_TRUE(EventQueue_IsEmpty(&queue));
}

void test_EventQueue_Peek(void) {
    TEvent event = {TEST_SIG_1, NULL, 0};
    EventQueue_Enqueue(&queue, event);

    TEvent peekedEvent = EventQueue_Peek(&queue);

    TEST_ASSERT_EQUAL_INT(TEST_SIG_1, peekedEvent.sig);
}

void test_EventQueue_IsEmpty(void) {
    TEST_ASSERT_TRUE(EventQueue_IsEmpty(&queue));
}

void test_EventQueue_IsFull(void) {
    for (int i = 0; i < QUEUE_MAX_CAPACITY; ++i) {
        TEvent event = {i, NULL, 0};
        bool enqueueResult = EventQueue_Enqueue(&queue, event);
        TEST_ASSERT_TRUE(enqueueResult);
    }

    TEST_ASSERT_TRUE(EventQueue_IsFull(&queue));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_EventQueue_Initialize);
    RUN_TEST(test_EventQueue_Enqueue);
    RUN_TEST(test_EventQueue_Dequeue);
    RUN_TEST(test_EventQueue_Peek);
    RUN_TEST(test_EventQueue_IsEmpty);
    RUN_TEST(test_EventQueue_IsFull);
    return UNITY_END();
}
