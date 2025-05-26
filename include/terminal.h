#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include "defines.h"

void terminal_iniciar();
void terminal_finalizar();
void terminal_limpar_tela();
void terminal_ir_topo_esquerda();
void terminal_ir_para_xy(int linha, int coluna);
void terminal_definir_cor(TerminalCor cor);
int terminal_ler_char_noblock();
void terminal_dormir_micros(long usec);
void terminal_limpar_buffer_entrada();

#endif
