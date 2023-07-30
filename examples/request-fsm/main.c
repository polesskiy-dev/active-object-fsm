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
    REQUEST_SIG_MAX,
} REQUEST_SIG;

typedef enum {
    REQUEST_NO_ST,
    PENDING_ST,
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
        "REQUEST_NO_ST", "PENDING_ST", "SUCCESS_ST", "ERROR_ST"
};

DECLARE_ACTIVE_OBJECT(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_AO_ID, REQUEST_QUEUE_MAX_CAPACITY);
DECLARE_FSM(REQUEST_AO, REQUEST_EVENT, REQUEST_STATE, REQUEST_SIG_MAX, REQUEST_ST_MAX);

/**
 * Application and local declarations
 */
REQUEST_AO requestActiveObject;

void runTasks();
bool canRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE performRequest(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE requestError(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE requestSuccess(REQUEST_AO *const activeObject, REQUEST_EVENT event);
REQUEST_STATE processEventToNextState(REQUEST_AO *const activeObject, REQUEST_EVENT event);

DECLARE_GUARD(REQUEST_AO, REQUEST_EVENT, canRetry, performRequest, requestError);

// state transitions table, [state][event] => state handler f pointer
REQUEST_STATE_HANDLE_F requestTransitionTable[REQUEST_ST_MAX][REQUEST_SIG_MAX] = {
        [REQUEST_NO_ST]=    {[MAKE_REQUEST_SIG]=performRequest},
        [PENDING_ST]=       {[REQUEST_SUCCESS_SIG]=requestSuccess, [REQUEST_ERROR_SIG]=GUARD(canRetry, performRequest, requestError), [TIMEOUT_SIG]=GUARD(canRetry, performRequest, requestError)}
};

// TODO should we pass cb to state transition?
int maxRetries = 4;

int main(void) {
    REQUEST_AO_Ctor(&requestActiveObject, REQUEST_NO_ST);

    printf("Starting Request FSM\n");
    printf("Dispatching MAKE REQUEST Event\n");
    REQUEST_AO_Dispatch(&requestActiveObject, (REQUEST_EVENT){.sig=MAKE_REQUEST_SIG});
    runTasks();
    printf("REQUEST AO state is: %s \n", STATES_STRINGS[requestActiveObject.state]);

    printf("Dispatching ERROR Event\n");
    REQUEST_AO_Dispatch(&requestActiveObject, (REQUEST_EVENT){.sig=REQUEST_ERROR_SIG});
    runTasks();
    printf("REQUEST AO state is: %s \n", STATES_STRINGS[requestActiveObject.state]);

    printf("Dispatching TIMEOUT Event\n");
    REQUEST_AO_Dispatch(&requestActiveObject, (REQUEST_EVENT){.sig=TIMEOUT_SIG});
    runTasks();
    printf("REQUEST AO state is: %s \n", STATES_STRINGS[requestActiveObject.state]);

    return 0;
}

void runTasks() {
    REQUEST_AO_ProcessQueue(&requestActiveObject, processEventToNextState, NULL);
};

REQUEST_STATE performRequest(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    return PENDING_ST;
}

bool canRetry(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    printf("Guard check whether we can retry\n");
    return true;
};

REQUEST_STATE processEventToNextState(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    return REQUEST_AO_FSM_ProcessEventToNextState(activeObject, event, requestTransitionTable);
};

REQUEST_STATE requestError(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    printf("Request error occurs\n");
    return ERROR_ST;
};

REQUEST_STATE requestSuccess(REQUEST_AO *const activeObject, REQUEST_EVENT event) {
    printf("Request success occurs\n");
    return SUCCESS_ST;
}