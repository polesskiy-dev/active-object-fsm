#include "stdio.h"
#include "stdint.h"

#include "../../src/active-object/active_object.h"
#include "../../src/active-object/active_object_impl.h"
#include "../../src/fsm/fsm.h"

#define REQUEST_AO                      REQUEST_AO
#define REQUEST_AO_ID                   (0)
#define REQUEST_QUEUE_MAX_CAPACITY      (4)
#define NO_RETRIES_LEFT                 (0)
#define MAX_RETRIES                     (1)

typedef enum {
    NO_SIG,
    MAKE_REQUEST_SIG,
    REQUEST_SUCCESS_SIG,
    REQUEST_ERROR_SIG,
    TIMEOUT_SIG,
    REQUEST_SIG_MAX,
} REQUEST_SIG;

typedef enum {
    REQUEST_NO_ST,
    PENDING_ST,
    RETRY_WAIT_ST,
    SUCCESS_ST,
    ERROR_ST,
    REQUEST_ST_MAX,
} REQUEST_STATE;

typedef struct {
    REQUEST_SIG sig;
    void* payload;
} REQUEST_EVENT;

// for states debug representation
const char *const STATES_STRINGS[] = {
        "REQUEST_NO_ST", "PENDING_ST", "RETRY_WAIT_ST", "SUCCESS_ST", "ERROR_ST"
};

typedef struct {
    uint8_t maxRetries;
} REQUEST_AO_FIELDS;

DECLARE_ACTIVE_OBJECT(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_AO_FIELDS, REQUEST_QUEUE_MAX_CAPACITY);
ACTIVE_OBJECT_IMPLEMENTATION(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_AO_FIELDS, REQUEST_QUEUE_MAX_CAPACITY);
DECLARE_FSM(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_SIG_MAX, REQUEST_ST_MAX);

/**
 * Application and local declarations
 */
REQUEST_AO requestActiveObject;

void runTasks();
bool canRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE performRequest(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE waitForRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE requestError(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE requestSuccess(REQUEST_AO *const activeObject, REQUEST_EVENT event);
//REQUEST_STATE processEventToNextState(REQUEST_AO *const activeObject, REQUEST_EVENT event);

DECLARE_GUARD(REQUEST_AO, REQUEST_EVENT, canRetry, waitForRetry, requestError);

// state transitions table, [state][event] => state handler f pointer
REQUEST_EVENT_HANDLE_F requestTransitionTable[REQUEST_ST_MAX][REQUEST_SIG_MAX] = {
        [REQUEST_NO_ST]=    {[MAKE_REQUEST_SIG]=performRequest},
        [PENDING_ST]=       {[REQUEST_SUCCESS_SIG]=requestSuccess, [REQUEST_ERROR_SIG]=GUARD(canRetry, waitForRetry, requestError), [TIMEOUT_SIG]=GUARD(canRetry, waitForRetry, requestError)},
        [RETRY_WAIT_ST]=    {[MAKE_REQUEST_SIG]=performRequest}
};

int main(void) {
    printf("Starting Request with retry FSM\n\n");

    return 0;
};

bool canRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    if (activeObject->fields.maxRetries > NO_RETRIES_LEFT) return true;
    return false;
};

REQUEST_STATE waitForRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    printf("Waiting for retry (MAKE_REQUEST) event\n");

    return RETRY_WAIT_ST;
};
