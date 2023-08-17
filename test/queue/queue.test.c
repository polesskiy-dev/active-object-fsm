#include <string.h>

#include "./test.h"
#include "../../libraries/Unity/src/unity.h"
#include "../../src/queue/queue.h"

TQueue q;

void setUp(void) {
    // This is run before EACH test
    QUEUE_Ctor(&q); // constructor, BEWARE: it's not emptying actual elements
    memset(q.elements, 0, MAX_QUEUE_CAPACITY * sizeof(QUEUE_ELEMENT_T) );
}

void tearDown(void) {
    // This is run after EACH test
}

void test_queue_ctor(void) {
    TEST_ASSERT_EQUAL_INT(-1, q.front);
    TEST_ASSERT_EQUAL_INT(-1, q.rear);
    TEST_ASSERT_EQUAL_INT(0, QUEUE_GetSize(&q));
}

void test_queue_enqueue(void) {
    for (int i = 0; i < MAX_QUEUE_CAPACITY - 1; i++) {
        QUEUE_Enqueue(&q, i);
        TEST_ASSERT_EQUAL_INT(i+1, QUEUE_GetSize(&q));
    }
}

void test_queue_dequeue(void) {
    for (int i = 0; i < MAX_QUEUE_CAPACITY - 1; i++) {
        QUEUE_Enqueue(&q, i);
    }
    TEST_ASSERT_EQUAL_INT(0, QUEUE_Dequeue(&q));
    TEST_ASSERT_EQUAL_INT(MAX_QUEUE_CAPACITY-2, QUEUE_GetSize(&q));
}

void test_queue_isfull(void) {
    for (int i = 0; i < MAX_QUEUE_CAPACITY - 1; i++) {
        QUEUE_Enqueue(&q, i);
    }
    TEST_ASSERT_FALSE(QUEUE_IsFull(&q));
    QUEUE_Enqueue(&q, 99);
    TEST_ASSERT_TRUE(QUEUE_IsFull(&q));
}

void test_queue_dequeue_empty(void) {
    TEST_ASSERT_EQUAL_INT(0, QUEUE_Dequeue(&q));
    TEST_ASSERT_EQUAL_INT(0, QUEUE_GetSize(&q));
}

void test_queue_peek_empty(void) {
    TEST_ASSERT_EQUAL_INT(0, QUEUE_Peek(&q));
    TEST_ASSERT_EQUAL_INT(0, QUEUE_GetSize(&q));
}

void test_queue_enqueue_full(void) {
    for (int i = 0; i < MAX_QUEUE_CAPACITY; i++) {
        TEST_ASSERT_TRUE(QUEUE_Enqueue(&q, i));
    }
    TEST_ASSERT_FALSE(QUEUE_Enqueue(&q, 99));
    TEST_ASSERT_EQUAL_INT(MAX_QUEUE_CAPACITY, QUEUE_GetSize(&q));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_ctor);
    RUN_TEST(test_queue_enqueue);
    RUN_TEST(test_queue_dequeue);
    RUN_TEST(test_queue_isfull);
    RUN_TEST(test_queue_dequeue_empty);
    RUN_TEST(test_queue_peek_empty);
    RUN_TEST(test_queue_enqueue_full);

    return UNITY_END();
}
