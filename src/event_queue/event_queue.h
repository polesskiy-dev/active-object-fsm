/**
 * @file event_queue.h
 *
 * @brief Template Queue for a given data type
 *
 * @details This queue implementation is based on a circular queue, also known as a circular buffer.
 * It utilizes a fixed-size array and employs the concept of wrapping around the indices to achieve a circular behavior.
 * The circular nature allows efficient utilization of space without wasting memory.
 *
 * ### Example:
 * @code
 * #include "event_queue.h"
 * #define QUEUE_MAX_CAPACITY  (8)
 * @endcode
 *
 * @author apolisskyi
 */

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


/**
 * @brief Event structure containing a signal and payload
 */
typedef struct TEvent {
    int sig;            /**< Signal for event, possibly enums */
    void* payload;      /**< Pointer to payload */
    size_t size;        /**< Size of payload */
} TEvent;

/**
 * @brief Fixed-size Event Queue structure
 */
typedef struct TEventQueue {
    TEvent* events;         /**< Pointer to array holding the events */
    int32_t front;          /**< Front index */
    int32_t rear;           /**< Rear index */
    uint32_t capacity;      /**< Capacity of the queue */
} TEventQueue;

/**
 * @brief Initializes the Event Queue
 * @param queue The TEventQueue to initialize
 * @param events The array of TEvents to use
 * @param capacity The capacity of the queue
 */
void EventQueue_Initialize(TEventQueue* queue, TEvent* events, uint32_t capacity);

/**
 * @brief Enqueue an event into the queue
 * @param queue The TEventQueue pointer
 * @param event The TEvent to enqueue
 * @return true for success, false for failure
 */
bool EventQueue_Enqueue(TEventQueue* queue, TEvent event);

/**
 * @brief Dequeue an event from the queue
 * @param queue The TEventQueue pointer
 * @return The TEVent from the front of the queue
 */
TEvent EventQueue_Dequeue(TEventQueue* queue);

/**
 * @brief Peek the front event without removing it
 * @param queue The TEventQueue pointer
 * @return The TEVent at the front of the queue
 */
TEvent EventQueue_Peek(TEventQueue* queue);

/**
 * @brief Check if the queue is empty
 * @param queue The TEventQueue pointer
 * @return true if empty, false if not empty
*/
bool EventQueue_IsEmpty(TEventQueue* queue);

/**
 * @brief Check if the queue is full
 * @param queue The TEventQueue pointer
 * @return true if full, false if not full
*/
bool EventQueue_IsFull(TEventQueue* queue);

#endif // EVENT_QUEUE_H
