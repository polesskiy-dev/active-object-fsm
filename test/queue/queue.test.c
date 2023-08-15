#include "../../libraries/Unity/src/unity.h"
#include "../../src/queue/queue.h"
#include "../../src/queue/queue_impl.h"

// We're using a queue of integers for simplicity
#define QUEUE_SIZE 4
DECLARE_QUEUE(int, QUEUE_SIZE)
QUEUE_IMPLEMENTATION(int, QUEUE_SIZE)

QUEUE_int q;

void setUp(void) {
    // This is run before EACH test
    QUEUE_int_Ctor(&q); // constructor, BEWARE: it's not emptying actual elements
}

void tearDown(void) {
    // This is run after EACH test
}

void test_queue_ctor(void) {
    TEST_ASSERT_EQUAL_INT(-1, q.front);
    TEST_ASSERT_EQUAL_INT(-1, q.rear);
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_GetSize(&q));
}

void test_queue_enqueue(void) {
    for (int i = 0; i < QUEUE_SIZE - 1; i++) {
        QUEUE_int_Enqueue(&q, i);
        TEST_ASSERT_EQUAL_INT(i+1, QUEUE_int_GetSize(&q));
    }
}

void test_queue_dequeue(void) {
    for (int i = 0; i < QUEUE_SIZE - 1; i++) {
        QUEUE_int_Enqueue(&q, i);
    }
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_Dequeue(&q));
    TEST_ASSERT_EQUAL_INT(QUEUE_SIZE-2, QUEUE_int_GetSize(&q));
}

void test_queue_isfull(void) {
    for (int i = 0; i < QUEUE_SIZE - 1; i++) {
        QUEUE_int_Enqueue(&q, i);
    }
    TEST_ASSERT_FALSE(QUEUE_int_IsFull(&q));
    QUEUE_int_Enqueue(&q, 99);
    TEST_ASSERT_TRUE(QUEUE_int_IsFull(&q));
}

void test_queue_dequeue_empty(void) {
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_Dequeue(&q));
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_GetSize(&q));
}

void test_queue_peek_empty(void) {
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_Peek(&q));
    TEST_ASSERT_EQUAL_INT(0, QUEUE_int_GetSize(&q));
}

void test_queue_enqueue_full(void) {
    for (int i = 0; i < QUEUE_SIZE; i++) {
        TEST_ASSERT_TRUE(QUEUE_int_Enqueue(&q, i));
    }
    TEST_ASSERT_FALSE(QUEUE_int_Enqueue(&q, 99));
    TEST_ASSERT_EQUAL_INT(QUEUE_SIZE, QUEUE_int_GetSize(&q));
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
