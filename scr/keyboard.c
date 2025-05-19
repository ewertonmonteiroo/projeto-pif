#include "keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static struct termios oldt, newt;

void keyboardInit() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void keyboardDestroy() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int keyhit() {
    int byteswaiting;
    ioctl(STDIN_FILENO, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

int readch() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}
