#include "stdio.h"
#include "stdint.h"

#include "../../src/queue/queue.h"
#include "../../src/active-object/active-object.h"
#include "../../src/fsm/fsm.h"

#define REQUEST_AO                   REQUEST_AO
#define REQUEST_QUEUE_MAX_CAPACITY   (8)

typedef enum {
    REQUEST_AO_ID
} ACTIVE_OBJECT_ID;

typedef enum {
    MAKE_REQUEST_SIG,
    REQUEST_SUCCESS_SIG,
    REQUEST_ERROR_SIG,
    TIMEOUT_SIG,
    REQUEST_MAX_SIG,
} REQUEST_SIG;

typedef enum {
    REQUEST_NO_ST,
    PENDING_ST,
    SUCCESS_ST,
    ERROR_ST,
    REQUEST_MAX_ST,
} REQUEST_STATE;

typedef struct {
    REQUEST_SIG sig;
    void* payload;
} REQUEST_EVENT;

// for states debug representation
const char *const STATES_STRINGS[] = {
        "REQUEST_NO_ST", "PENDING_ST", "SUCCESS_ST", "ERROR_ST"
};

/**
 * Active Object Declarations
 */
DECLARE_ACTIVE_OBJECT(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_AO_ID, REQUEST_QUEUE_MAX_CAPACITY);

/**
 * Application and local declarations
 */
REQUEST_AO requestActiveObject;

void runTasks();

int main(void) {
    REQUEST_AO_Ctor(&requestActiveObject, REQUEST_NO_ST);

    printf("Starting Request FSM\n");
    printf("Dispatching MAKE REQUEST Event\n");
    REQUEST_AO_Dispatch(&requestActiveObject, (REQUEST_EVENT){.sig=MAKE_REQUEST_SIG});
    runTasks();
    printf("REQUEST AO state is: %s \n", STATES_STRINGS[requestActiveObject.state]);

    return 0;
}

void runTasks() {
    // TODO implement FSM
};