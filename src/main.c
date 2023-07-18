#include "unity.h"
#include "queue/queue.h"

DECLARE_QUEUE(int)

void setUp(void) {
    // Set up any necessary resources before each test
}

void tearDown(void) {
    // Clean up any resources after each test
}

void test_QueueEnqueueDequeue(void) {
    QUEUE_int queue;
    QUEUE_int_Init(&queue);

    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 0);

    QUEUE_int_Enqueue(&queue, 10);
    QUEUE_int_Enqueue(&queue, 20);
    QUEUE_int_Enqueue(&queue, 30);

    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == 3);
    TEST_ASSERT_TRUE(QUEUE_int_Peek(&queue) == 10);

    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 10);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 20);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 30);

    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Peek(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 0);
}

void test_QueueFull(void) {
    QUEUE_int queue;
    QUEUE_int_Init(&queue);

    // Enqueue elements until the queue is full
    for (int i = 0; i < QUEUE_MAX_CAPACITY; i++) {
        QUEUE_int_Enqueue(&queue, i);
    }

    // Queue is now full
    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == QUEUE_MAX_CAPACITY);

    // Attempt to enqueue one more element (should fail)
    QUEUE_int_Enqueue(&queue, 100);

    // Size and front/rear should remain unchanged
    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == QUEUE_MAX_CAPACITY);
    TEST_ASSERT_TRUE(QUEUE_int_Peek(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 0);
}

void test_QueueEmpty(void) {
    QUEUE_int queue;
    QUEUE_int_Init(&queue);

    // Queue is empty
    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Peek(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 0);

    // Enqueue an element
    QUEUE_int_Enqueue(&queue, 10);

    // Dequeue the enqueued element
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 10);

    // Queue is now empty again
    TEST_ASSERT_TRUE(QUEUE_int_GetSize(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Peek(&queue) == 0);
    TEST_ASSERT_TRUE(QUEUE_int_Dequeue(&queue) == 0);
}

int main(void) {
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_QueueEnqueueDequeue);
    RUN_TEST(test_QueueFull);
    RUN_TEST(test_QueueEmpty);

    return UNITY_END();
}