/**
 * @file queue.h
 *
 * @brief Generic Queue for Embedded Systems.
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 *
 * Key features include:
 *  - Statically allocated memory, ensuring predictable memory usage.
 *  - FIFO (First In, First Out) data structure.
 *  - Functions to check if the queue is full or empty.
 *  - Peek functionality to inspect the front of the queue without removal.
 *
 * To use the queue module, a specific data type `QUEUE_ELEMENT_T` should be defined
 * before including this header. This type represents the datatype the queue will store.
 *
 * ###Example:
 * @code
 * typedef struct {
 *     int data;
 * } QUEUE_ELEMENT_T;
 *
 * #define QUEUE_ELEMENT_T QUEUE_ELEMENT_T
 * #include "queue.h"
 * @endcode
 *
 * For further details on individual functions, refer to their respective documentation.
 *
 * @note This queue does not dynamically allocate memory and relies on a predefined
 * maximum size (`MAX_QUEUE_CAPACITY`). Ensure that the queue's capacity meets the
 * application's requirements.
 *
 * @author apolisskyi
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef QUEUE_ELEMENT_T
#error "Please define QUEUE_ELEMENT_T before including queue.h"
#define QUEUE_ELEMENT_T int // just for debug
#endif

#ifndef MAX_QUEUE_CAPACITY
/** suggested max queue capacity */
#define MAX_QUEUE_CAPACITY  (16)
#endif

/**
* @brief Queue struct.
*
* Represents a queue using a circular buffer mechanism.
* The queue's capacity is defined by `MAX_QUEUE_CAPACITY`.
*
* @var front - Index of the front element in the queue.
* @var rear - Index of the rear element in the queue.
* @var elements[MAX_QUEUE_CAPACITY] - Holds the elements of the queue.
*/
typedef struct {
    int8_t front;
    int8_t rear;
    QUEUE_ELEMENT_T elements[MAX_QUEUE_CAPACITY];
} TQueue;

/**
 * @brief Constructor. Initializes the queue.
 * @attention this constructor does not clear out the elements
 *
 * @param q Pointer to the queue.
 *
 * ###Example:
 * @code
 * TQueue q;
 * QUEUE_Ctor(&q);
 * @endcode
*/
void QUEUE_Ctor(TQueue *const q);

/**
 * @brief Enqueues an element into the queue.
 *
 * @param q Pointer to the queue.
 * @param elem Element to enqueue.
 * @return true if the enqueue operation was successful, false otherwise e.g. max capacity reach.
 *
 * ###Example:
 * @code
 * QUEUE_ELEMENT_T elem = {.data = 1};
 * bool success = QUEUE_Enqueue(&q, elem);
 * @endcode
 */
bool QUEUE_Enqueue(TQueue *const q, QUEUE_ELEMENT_T elem);

/**
 * @brief Dequeues an element from the queue.
 *
 * @param q Pointer to the queue.
 * @return The dequeued element. Check with QUEUE_IsEmpty before using this function.
 *
 * ###Example:
 * @code
 * if (!QUEUE_IsEmpty(&q)) {
 *     QUEUE_ELEMENT_T dequeuedElem = QUEUE_Dequeue(&q);
 * }
 * @endcode
 */
QUEUE_ELEMENT_T QUEUE_Dequeue(TQueue *const q);

/**
 * @brief Retrieves the size of the queue.
 *
 * @param q Pointer to the queue.
 * @return The current size of the queue.
 *
 * ###Example:
 * @code
 * int8_t size = QUEUE_GetSize(&q);
 * @endcode
 */
int8_t QUEUE_GetSize(TQueue *const q);

/**
 * @brief Peeks at the front element without dequeuing it.
 *
 * @param q Pointer to the queue.
 * @return The front element. Check with QUEUE_IsEmpty before using this function.
 *
 * ###Example:
 * @code
 * if (!QUEUE_IsEmpty(&q)) {
 *     QUEUE_ELEMENT_T frontElem = QUEUE_Peek(&q);
 * }
 * @endcode
 */
QUEUE_ELEMENT_T QUEUE_Peek(TQueue *const q);

/**
 * @brief Checks if the queue is full.
 *
 * @param q Pointer to the queue.
 * @return True if the queue is full, false otherwise.
 *
 * ###Example:
 * @code
 * if (QUEUE_IsFull(&q)) {
 *     // Handle the queue full scenario.
 * }
 * @endcode
 */
bool QUEUE_IsFull(TQueue *const q);

/**
 * @brief Checks if the queue is empty.
 *
 * @param q Pointer to the queue.
 * @return True if the queue is empty, false otherwise.
 *
 * ###Example:
 * @code
 * if (QUEUE_IsEmpty(&q)) {
 *     // Handle the queue empty scenario.
 * }
 * @endcode
 */
bool QUEUE_IsEmpty(TQueue *const q);

#ifdef __cplusplus
}
#endif

#endif
