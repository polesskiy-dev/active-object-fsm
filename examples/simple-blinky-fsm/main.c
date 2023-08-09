#include "stdio.h"
#include "stdint.h"

#include "../../src/queue/queue.h"
#include "../../src/active-object/active-object.h"

#define BLINKY_AO                   BLINKY_AO
#define BLINKY_QUEUE_MAX_CAPACITY   (8)

typedef enum {
    AO_BLINKY_ID
} ACTIVE_OBJECT_ID;

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

/**
 * Active Object Declarations
 */
DECLARE_ACTIVE_OBJECT(BLINKY_AO, BLINKY_EVENT, BLINKY_STATE, void*, AO_BLINKY_ID, BLINKY_QUEUE_MAX_CAPACITY);

/**
 * Application and local declarations
 */
BLINKY_AO blinkyActiveObject;

void runTasks();
/** local FSM functions, */
BLINKY_STATE LOCAL_FSM_GetNextState(BLINKY_AO * const activeObject, BLINKY_EVENT e);
BLINKY_STATE LOCAL_FSM_ProcessEvent(BLINKY_AO * const activeObject, BLINKY_EVENT e);

// TODO get rid of INIT state

int main(void) {
    BLINKY_AO_Ctor(&blinkyActiveObject, BLINKY_NO_ST, NULL);

    printf("Starting Blinky FSM\n");
    printf("Dispatching INIT Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_INIT_SIG});
    runTasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    // turn on
    printf("LED ON Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_ON_SIG});
    runTasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);
    printf("LED ON Event, one more time \n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_ON_SIG});
    runTasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    // turn OFF
    printf("LED OFF Event\n");
    BLINKY_AO_Dispatch(&blinkyActiveObject, (BLINKY_EVENT){.sig=BLINKY_LED_OFF_SIG});
    runTasks();
    printf("BLINKY state is: %s \n", STATES_STRINGS[blinkyActiveObject.state]);

    return 0;
}

BLINKY_STATE LOCAL_FSM_GetNextState(BLINKY_AO * const activeObject, BLINKY_EVENT e) {
    const BLINKY_STATE currState = activeObject->state;

    switch(currState) {
        case BLINKY_NO_ST:
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

void runTasks() {
    BLINKY_AO_ProcessQueue(&blinkyActiveObject, &LOCAL_FSM_ProcessEvent, NULL);
}

BLINKY_STATE LOCAL_FSM_ProcessEvent(BLINKY_AO *const activeObject, BLINKY_EVENT e) {
    BLINKY_STATE nextState = LOCAL_FSM_GetNextState(activeObject, e);

    return nextState;
};
