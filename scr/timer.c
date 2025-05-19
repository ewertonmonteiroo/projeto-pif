#include "timer.h"
#include <time.h>

static clock_t lastTime;
static int timerInterval;

void timerInit(int microseconds) {
    timerInterval = microseconds;
    lastTime = clock();
}

int timerTimeOver() {
    clock_t currentTime = clock();
    if ((currentTime - lastTime) * 1000 / CLOCKS_PER_SEC >= timerInterval) {
        lastTime = currentTime;
        return 1;
    }
    return 0;
}

void timerDestroy() {}