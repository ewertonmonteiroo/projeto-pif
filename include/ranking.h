#ifndef RANKING_H
#define RANKING_H

#include "defines.h"

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} EntradaRanking;

void salvar_pontuacao(const char *nome, int pontuacao);
void mostrar_ranking();

#endif
