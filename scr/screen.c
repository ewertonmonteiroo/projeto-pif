#include "screen.h"
#include <stdio.h>

void screenInit() {}
void screenDestroy() {}

void screenClear() {
    printf("\033[H\033[J");
}

void screenUpdate() {
    fflush(stdout);
}