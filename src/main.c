#include <stdio.h>

#include "event/event.h"
#include "queue/queue.h"

DECLARE_QUEUE(AO_EVENT);

QUEUE_AO_EVENT q;

int main(void) {
    QUEUE_AO_EVENT_Init(&q);
    // QUEUE_Init_AO_EVENT(&q, (AO_Event){.sig = EXIT_SIG});

    // printf("%d\n", q.array[0].sig);

    return 0;
}
