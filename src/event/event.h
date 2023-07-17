#ifndef EVENT_H
#define EVENT_H

typedef enum {
	INIT_SIG,
	EXIT_SIG
} AO_SIGNAL;

typedef struct {
    AO_SIGNAL sig;
    void* payload;
} AO_EVENT;

#endif
