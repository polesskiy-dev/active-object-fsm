#include "stdio.h"
#include "stdint.h"

#include "../../src/event/event.h"
#include "../../src/queue/queue.h"
#include "../../src/active-object/active-object.h"

#define BLINKY_AO                   BLINKY_AO
#define BLINKY_QUEUE_MAX_CAPACITY   (8)
#define EMPTY_QUEUE                 (0)

typedef enum {
    BLINKY_NO_SIG,
    BLINKY_INIT_SIG,
    BLINKY_LED_ON_SIG,
    BLINKY_LED_OFF_SIG,
    BLINKY_MAX_SIG,
} BLINKY_SIG;

typedef enum {
    BLINKY_NO_ST,
    BLINKY_INIT_ST,
    BLINKY_LED_ON_ST,
    BLINKY_LED_OFF_ST,
    BLINKY_MAX_ST,
} BLINKY_STATE;

typedef struct {
    BLINKY_SIG sig;
    void* payload;
} BLINKY_EVENT;

// for states debug representation
const char *const STATES_STRINGS[] = {
        "BLINKY_NO_ST", "BLINKY_INIT_ST", "BLINKY_LED_ON_ST", "BLINKY_LED_OFF_ST"
};

DECLARE_ACTIVE_OBJECT(BLINKY_AO, BLINKY_EVENT, BLINKY_STATE, BLINKY_QUEUE_MAX_CAPACITY, BLINKY_MAX_SIG, BLINKY_MAX_ST);
//DECLARE_FSM(BLINKY_AO, BLINKY_EVENT, BLINKY_STATE, BLINKY_MAX_SIG, BLINKY_MAX_ST);

BLINKY_AO blinkyActiveObject;

void AO_Tasks();
BLINKY_STATE AO_getNextState(BLINKY_AO * const activeObject, BLINKY_EVENT e);
void AO_processQueue(BLINKY_AO * const activeObject);
void AO_handleEvent(BLINKY_AO * const activeObject, BLINKY_EVENT e);
void AO_processToNextState(BLINKY_AO * const activeObject, BLINKY_STATE nextState);

int main(void) {
    BLINKY_AO_Ctor(&blinkyActiveObject, BLINKY_INIT_ST);

    printf("Starting Blinky FSM\n");
    printf("Dispatching INIT Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_INIT_SIG});
    AO_Tasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    // turn on
    printf("LED ON Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_ON_SIG});
    AO_Tasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);
    printf("LED ON Event, one more time \n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_ON_SIG});
    AO_Tasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    // turn OFF
    printf("LED OFF Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_OFF_SIG});
    AO_Tasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    return 0;
}

BLINKY_STATE AO_getNextState(BLINKY_AO * const activeObject, BLINKY_EVENT e) {
    const BLINKY_STATE currState = activeObject->state;

    switch(currState) {
        case BLINKY_INIT_ST:
            switch (e.sig) {
                case BLINKY_INIT_SIG:
                    return BLINKY_INIT_ST;
                case BLINKY_LED_ON_SIG:
                    return BLINKY_LED_ON_ST;
            }
            break;
        case BLINKY_LED_ON_ST:
            switch (e.sig) {
                case BLINKY_LED_OFF_SIG:
                    return BLINKY_LED_OFF_ST;
            }
            break;
        case BLINKY_LED_OFF_ST:
            switch (e.sig) {
                case BLINKY_LED_ON_SIG:
                    return BLINKY_LED_ON_ST;
            }
            break;
    }

    return currState;
};

void AO_Tasks() {
    AO_processQueue(&blinkyActiveObject);
}

void AO_processQueue(BLINKY_AO * const activeObject) {
    bool isEmptyQueue = EMPTY_QUEUE == QUEUE_BLINKY_EVENT_GetSize(&activeObject->queue);

    if (!isEmptyQueue) {
        BLINKY_EVENT e = QUEUE_BLINKY_EVENT_Dequeue(&activeObject->queue);
        AO_handleEvent(activeObject, e);
    }
};

void AO_handleEvent(BLINKY_AO * const activeObject, BLINKY_EVENT e) {
    BLINKY_STATE nextState = AO_getNextState(activeObject, e);
    // set state
    AO_processToNextState(activeObject, nextState);
};

void AO_processToNextState(BLINKY_AO * const activeObject, BLINKY_STATE nextState) {
    activeObject->state = nextState;
}
