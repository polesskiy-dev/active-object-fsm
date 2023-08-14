/**
 * @file queue.h
 *
 * @brief Template Queue for a given data type
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 *
 * @author apolisskyi
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
 * @def DECLARE_QUEUE(T, maxQueueCapacity)
 * @brief Declares a generic queue for the type `T` with a maximum capacity of `maxQueueCapacity`.
 *
 * @tparam T The data type of the elements in the queue.
 * @tparam maxQueueCapacity max queue capacity (size), should always be a power of 2, not more than 128 (int8)
 *
 * ####Example:
 * @code
 * // Declare a queue for integers with a maximum capacity of 10
 * DECLARE_QUEUE(int, 10);
 * @endcode
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

/**
 * @struct QUEUE_T
 * @brief Struct for defining the Queue
 *
 * @param front head T element
 * @param rear tail T element
 * @param elements array of T elements, static size
 */

/* should never be defined, for documentation purpose only */
#ifdef DOXYGEN_ONLY

/**
 * @brief Queue constructor.
 *
 * @param q Pointer to the queue to be initialized.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * @endcode
 */
void QUEUE_T_Ctor(QUEUE_T *const q);

/**
 * @brief Enqueues an element into the queue.
 *
 * @param q Pointer to the queue.
 * @param item The item to be enqueued.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * @endcode
 */
void QUEUE_T_Enqueue(QUEUE_T *const q, T item);

/**
 * @brief Dequeues an element from the queue.
 *
 * @param q Pointer to the queue.
 * @return The dequeued item.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int item = QUEUE_int_Dequeue(&q);
 * @endcode
 */
T QUEUE_T_Dequeue(QUEUE_T *const q);

/**
 * @brief Gets the current size of the queue.
 *
 * @param q Pointer to the queue.
 * @return The current size of the queue.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int size = QUEUE_int_GetSize(&q);  // size will be 1
 * @endcode
 */
int QUEUE_T_GetSize(QUEUE_T *const q);

/**
 * @brief Peeks at the front element of the queue.
 *
 * @param q Pointer to the queue.
 * @return The element at the front of the queue.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * QUEUE_int_Enqueue(&q, 5);
 * int frontItem = QUEUE_int_Peek(&q);  // frontItem will be 5
 * @endcode
 */
T QUEUE_T_Peek(QUEUE_T *const q)

/**
 * @brief Checks if the queue is full.
 *
 * @param q Pointer to the queue.
 * @return `true` if the queue is full, `false` otherwise.
 *
 * ####Example:
 * @code
 * QUEUE_int q;
 * QUEUE_int_Ctor(&q);
 * for (int i = 0; i < 10; i++) {
 *     QUEUE_int_Enqueue(&q, i);
 * }
 * bool isFull = QUEUE_int_IsFull(&q);  // isFull will be true
 * @endcode
 */
bool QUEUE_T_IsFull(QUEUE_T *const q);

#endif

#endif
