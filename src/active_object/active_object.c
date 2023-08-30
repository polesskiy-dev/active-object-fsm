#include "./active_object.h"

void ActiveObject_Initialize(TActiveObject* me, const uint8_t id, TEvent* events, uint32_t capacity) {
    me->id = id;
    me->state = NULL;
    EventQueue_Initialize(&me->queue, events, capacity);
}

void ActiveObject_Dispatch(TActiveObject* me, TEvent event) {
    EventQueue_Enqueue(&me->queue, event);
}

TEvent ActiveObject_ProcessQueue(TActiveObject* me) {
    if (EventQueue_IsEmpty(&me->queue)) {
        return (TEvent){.sig = 0, .payload = NULL, .size = 0};
    };

    return EventQueue_Dequeue(&me->queue);
}
