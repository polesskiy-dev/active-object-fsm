/**
 * @file queue.h
 *
 * @version 0.0.1
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

/** suggested max queue capacity */
#define QUEUE_MAX_CAPACITY (16)

// TODO check how to Doxygen internal template functions

/**
 * @brief Declare a queue template for a given data type.
 *
 * @param T The data type for the elements in the queue.
 * @param maxQueueCapacity max queue capacity (size), should always be a power of 2, not more than 128 (int8)
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 */
#define DECLARE_QUEUE(T, maxQueueCapacity) \
    typedef struct { \
        int8_t front; \
        int8_t rear; \
        T elements[maxQueueCapacity]; \
    } QUEUE_##T; \
    \
    /**
     * @brief Initialize the queue.
     *
     * @tparam T
     * @param [out] q Pointer to the queue to be initialized.
     */ \
    void QUEUE_##T##_Ctor(QUEUE_##T *const q) { \
        q->front = -1; \
        q->rear = -1; \
    } \
    \
    /**
     * @brief Enqueue an element into the queue.
     *
     * @tparam T
     * @param [in/out] q Pointer to the queue.
     * @param [in] item The item to be enqueued.
     */ \
    void QUEUE_##T##_Enqueue(QUEUE_##T *const q, T item) { \
        if (((q->rear + 1) % (maxQueueCapacity)) == q->front) { \
            printf("Queue is full. Cannot enqueue.\n"); \
            return; \
        } \
        \
        q->rear = (q->rear + 1) % (maxQueueCapacity); \
        q->elements[q->rear] = item; \
        if (q->front == -1) { \
            q->front = 0; \
        } \
    } \
    \
    /**
     * @brief Dequeue an element from the queue.
     *
     * @tparam T
     * @param [in/out] q Pointer to the queue.
     * @return The dequeued item.
     */ \
    T QUEUE_##T##_Dequeue(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot dequeue.\n"); \
            return (T){0}; \
        } \
        \
        T item = q->elements[q->front]; \
        if (q->front == q->rear) { \
            q->front = -1; \
            q->rear = -1; \
        } else { \
            q->front = (q->front + 1) % (maxQueueCapacity); \
        } \
        \
        return item; \
    } \
    \
    /**
     * @brief Get the current size of the queue.
     *
     * @tparam T
     * @param [in/out] q Pointer to the queue.
     * @return The current size of the queue.
     */ \
    int QUEUE_##T##_GetSize(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            return 0; \
        } \
        \
        if (q->rear >= q->front) { \
            return q->rear - q->front + 1; \
        } else { \
            return ((maxQueueCapacity) - q->front) + (q->rear + 1); \
        } \
    } \
    \
    /**
     * @brief Peek at the front element of the queue.
     *
     * @tparam T
     * @param [in/out] q Pointer to the queue.
     * @return The element at the front of the queue.
     */ \
    T QUEUE_##T##_Peek(QUEUE_##T *const q) { \
        if (q->front == -1) { \
            printf("Queue is empty. Cannot peek.\n"); \
            return (T){0}; \
        } \
        \
        return q->elements[q->front]; \
    }

/** @} */

#endif
