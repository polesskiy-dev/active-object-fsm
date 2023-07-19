/**
 * @file queue.h
 *
 * @author apolisskyi
 * @brief Template Queue for Events
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/**
 * @name QUEUE TEMPLATE
 *
 * @{
 */

/** Max queue capacity (size) should always be a power of 2, not more than 128 (int8) */
#define QUEUE_MAX_CAPACITY 16

// TODO check how to Doxygen internal template functions

/**
 * @brief Declare a queue template for a given data type.
 *
 * @param type The data type for the elements in the queue.
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 */
#define DECLARE_QUEUE(type) \
    typedef struct { \
        int8_t front; \
        int8_t rear; \
        type elements[QUEUE_MAX_CAPACITY]; \
    } QUEUE_##type; \
    \
    /**
     * @brief Initialize the queue.
     *
     * @tparam type
     * @param [out] q Pointer to the queue to be initialized.
     */ \
    void QUEUE_##type##_Init(QUEUE_##type *q) { \
        q->front = -1; \
        q->rear = -1; \
    } \
    \
    /**
     * @brief Enqueue an element into the queue.
     *
     * @tparam type
     * @param [in/out] q Pointer to the queue.
     * @param [in] item The item to be enqueued.
     */ \
    void QUEUE_##type##_Enqueue(QUEUE_##type *q, type item) { \
        if (((q->rear + 1) % QUEUE_MAX_CAPACITY) == q->front) { \
            printf("Queue is full. Cannot enqueue.\n"); \
            return; \
        } \
        \
        q->rear = (q->rear + 1) % QUEUE_MAX_CAPACITY; \
        q->elements[q->rear] = item; \
        if (q->front == -1) { \
            q->front = 0; \
        } \
    } \
    \
    /**
     * @brief Dequeue an element from the queue.
     *
     * @tparam type
     * @param [in/out] q Pointer to the queue.
     * @return The dequeued item.
     */ \
    type QUEUE_##type##_Dequeue(QUEUE_##type *q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot dequeue.\n"); \
            return (type)0; \
        } \
        \
        type item = q->elements[q->front]; \
        if (q->front == q->rear) { \
            q->front = -1; \
            q->rear = -1; \
        } else { \
            q->front = (q->front + 1) % QUEUE_MAX_CAPACITY; \
        } \
        \
        return item; \
    } \
    \
    /**
     * @brief Get the current size of the queue.
     *
     * @tparam type
     * @param [in/out] q Pointer to the queue.
     * @return The current size of the queue.
     */ \
    int QUEUE_##type##_GetSize(QUEUE_##type *q) { \
        if (q->front == -1) { \
            return 0; \
        } \
        \
        if (q->rear >= q->front) { \
            return q->rear - q->front + 1; \
        } else { \
            return (QUEUE_MAX_CAPACITY - q->front) + (q->rear + 1); \
        } \
    } \
    \
    /**
     * @brief Peek at the front element of the queue.
     *
     * @tparam type
     * @param [in/out] q Pointer to the queue.
     * @return The element at the front of the queue.
     */ \
    type QUEUE_##type##_Peek(QUEUE_##type *q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot peek.\n"); \
            return (type)0; \
        } \
        \
        return q->elements[q->front]; \
    }

/** @} */

#endif
