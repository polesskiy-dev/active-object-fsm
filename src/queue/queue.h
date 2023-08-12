/**
 * @file queue.h
 *
 * @version 0.0.1
 * @author apolisskyi
 *
 * @brief Template Queue for a given data type
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/** suggested max queue capacity */
#define QUEUE_MAX_CAPACITY  (16)
#define EMPTY_QUEUE         (0)

/**
 * @struct QUEUE_##T
 */

/**
 * @fn void QUEUE_##T##_Ctor(QUEUE_##T *const q)
 * @brief Queue constructor.
 *
 * @param q Pointer to the queue to be initialized.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 */

/**
 * @fn void QUEUE_##T##_Enqueue(QUEUE_##T *const q, T item)
 * @brief Enqueues an element into the queue.
 *
 * @param q Pointer to the queue.
 * @param item The item to be enqueued.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 */

/**
 * @fn T QUEUE_##T##_Dequeue(QUEUE_##T *const q)
 * @brief Dequeues an element from the queue.
 *
 * @param q Pointer to the queue.
 * @return The dequeued item.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int item = QUEUE_int_Dequeue(&q);
 */

/**
 * @fn int QUEUE_##T##_GetSize(QUEUE_##T *const q)
 * @brief Gets the current size of the queue.
 *
 * @param q Pointer to the queue.
 * @return The current size of the queue.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int size = QUEUE_int_GetSize(&q);  // size will be 1
 */

/**
 * @fn T QUEUE_##T##_Peek(QUEUE_##T *const q)
 * @brief Peeks at the front element of the queue.
 *
 * @param q Pointer to the queue.
 * @return The element at the front of the queue.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int frontItem = QUEUE_int_Peek(&q);  // frontItem will be 5
 */

/**
 * @fn bool QUEUE_##T##_IsFull(QUEUE_##T *const q)
 * @brief Checks if the queue is full.
 *
 * @param q Pointer to the queue.
 * @return `true` if the queue is full, `false` otherwise.
 *
 * @example
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * for (int i = 0; i < 10; i++) {
 *     QUEUE_int_Enqueue(&q, i);
 * }
 * bool isFull = QUEUE_int_IsFull(&q);  // isFull will be true
 */

/**
 * @def DECLARE_QUEUE(T, maxQueueCapacity)
 * Declares a generic queue for the type `T` with a maximum capacity of `maxQueueCapacity`.
 *
 * @param T The data type of the elements in the queue.
 * @param maxQueueCapacity max queue capacity (size), should always be a power of 2, not more than 128 (int8)
 *
 * @example
 * // Declare a queue for integers with a maximum capacity of 10
 * DECLARE_QUEUE(int, 10);
 */
#define DECLARE_QUEUE(T, maxQueueCapacity) \
    typedef struct { \
        int8_t front; \
        int8_t rear; \
        T elements[maxQueueCapacity]; \
    } QUEUE_##T; \
    void QUEUE_##T##_Ctor(QUEUE_##T *const q); \
    void QUEUE_##T##_Enqueue(QUEUE_##T *const q, T item); \
    T QUEUE_##T##_Dequeue(QUEUE_##T *const q); \
    int QUEUE_##T##_GetSize(QUEUE_##T *const q);          \
    T QUEUE_##T##_Peek(QUEUE_##T *const q); \
bool QUEUE_##T##_IsFull(QUEUE_##T *const q);

#endif
