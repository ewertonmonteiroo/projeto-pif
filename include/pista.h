#ifndef PISTA_H
#define PISTA_H

#include <stdlib.h>
#include "defines.h"

typedef struct {
    char **celulas;
    int largura;
    int altura;
} Pista;

Pista *criar_pista(int altura, int largura);
void liberar_pista(Pista *p);

#endif
