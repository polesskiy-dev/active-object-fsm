#include "stdio.h"
#include "stdint.h"

#include "../../src/fsm/fsm.h"
#include "../../src/fsm/fsm_impl.h"

/* Example of just using FSM, with no Active Object */

typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    STATES_MAX
} ELEVATOR_STATE;

typedef enum {
    BUTTON_UP_PRESSED,
    BUTTON_DOWN_PRESSED,
    EVENTS_MAX
} ELEVATOR_SIG;

typedef struct {
    ELEVATOR_SIG sig;
    uint8_t targetFloor;
} ELEVATOR_EVENT;

// Define the Active Object type, states, and events
typedef struct {
    ELEVATOR_STATE state;
    uint8_t currentFloor;
    uint8_t targetFloor;
} Elevator;

// for states debug representation
const char *const STATES_STRINGS[] = {
        "IDLE", "MOVING_UP", "MOVING_DOWN"
};

DECLARE_FSM(Elevator, ELEVATOR_EVENT, ELEVATOR_STATE, EVENTS_MAX, STATES_MAX);
FSM_IMPLEMENTATION(Elevator, ELEVATOR_EVENT, ELEVATOR_STATE, EVENTS_MAX, STATES_MAX);

// State handling functions
ELEVATOR_STATE handleIdle(Elevator *const elevator, ELEVATOR_EVENT event) {
    if (event.sig == BUTTON_UP_PRESSED) {
        elevator->targetFloor = event.targetFloor;
        return MOVING_UP;
    } else if (event.sig == BUTTON_DOWN_PRESSED) {
        elevator->targetFloor = event.targetFloor;
        return MOVING_DOWN;
    }
    return IDLE;
}

ELEVATOR_STATE handleMovingUp(Elevator *const elevator, ELEVATOR_EVENT event) {
    // Logic to move the elevator up...
    return MOVING_UP; // For simplicity, keep it moving up for this example
}

ELEVATOR_STATE handleMovingDown(Elevator *const elevator, ELEVATOR_EVENT event) {
    // Logic to move the elevator down...
    return MOVING_DOWN; // For simplicity, keep it moving down for this example
}

// Transition table
ELEVATOR_EVENT_HANDLE_F transitionTable[STATES_MAX][EVENTS_MAX] = {
        [IDLE][BUTTON_UP_PRESSED] = handleIdle,
        [IDLE][BUTTON_DOWN_PRESSED] = handleIdle,
        [MOVING_UP][BUTTON_UP_PRESSED] = handleMovingUp,
        [MOVING_UP][BUTTON_DOWN_PRESSED] = handleMovingUp,
        [MOVING_DOWN][BUTTON_UP_PRESSED] = handleMovingDown,
        [MOVING_DOWN][BUTTON_DOWN_PRESSED] = handleMovingDown,
};

int main() {
    Elevator myElevator = {.currentFloor = 0, .targetFloor = 0, .state = IDLE};

    printf("Elevator state: %s\n", STATES_STRINGS[myElevator.state]);

    ELEVATOR_EVENT event = {.sig = BUTTON_UP_PRESSED, .targetFloor = 3};
    printf("Pressing UP button, target floor %d\n", 3);

    // Use the FSM function
    myElevator.state = Elevator_FSM_ProcessEventToNextState(&myElevator, event, transitionTable);

    printf("Elevator state: %s\n", STATES_STRINGS[myElevator.state]);

    // ... rest of the code ...
}
