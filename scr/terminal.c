#include "terminal.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static struct termios termios_original;

static const char* ANSI_COLORS[] = {
    "\x1b[0m",   "\x1b[30m", "\x1b[31m", "\x1b[32m",
    "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m",
    "\x1b[37m", "\x1b[1;37m"
};

void terminal_iniciar() {
    struct termios cru;
    tcgetattr(STDIN_FILENO, &termios_original);
    cru = termios_original;
    cru.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &cru);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void terminal_finalizar() {
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_original);
    fcntl(STDIN_FILENO, F_SETFL, 0);
    terminal_definir_cor(COR_RESET);
    printf("\n");
}

void terminal_limpar_tela() {
    printf("\033[H\033[J");
}

void terminal_ir_topo_esquerda() {
    printf("\033[H");
}

void terminal_ir_para_xy(int linha, int coluna) {
    printf("\033[%d;%dH", linha, coluna);
}

void terminal_definir_cor(TerminalCor cor) {
    printf("%s", ANSI_COLORS[cor]);
}

int terminal_ler_char_noblock() {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    return -1;
}

void terminal_dormir_micros(long usec) {
    usleep(usec);
}

void terminal_limpar_buffer_entrada() {
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n');
}
