#ifndef EVENT_H
#define EVENT_H

typedef enum {
	INIT_SIG,
	EXIT_SIG
} AO_Signal;

typedef struct {
    AO_Signal sig;
    void* payload;
} AO_Event;

#endif
