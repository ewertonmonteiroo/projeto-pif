#include "pista.h"
#include <stdlib.h>
#include <string.h>

Pista *criar_pista(int altura, int largura) {
    Pista *p = malloc(sizeof(Pista));
    if (!p) return NULL;
    p->altura = altura;
    p->largura = largura;
    p->celulas = malloc(altura * sizeof(char*));
    if (!p->celulas) { free(p); return NULL; }

    for (int i = 0; i < altura; i++) {
        p->celulas[i] = malloc(largura * sizeof(char));
        if (!p->celulas[i]) {
            for (int k = 0; k < i; k++) free(p->celulas[k]);
            free(p->celulas); free(p); return NULL;
        }
        memset(p->celulas[i], CELULA_VAZIA, largura * sizeof(char));
    }
    return p;
}

void liberar_pista(Pista *p) {
    if (!p) return;
    for (int i = 0; i < p->altura; i++) {
        free(p->celulas[i]);
    }
    free(p->celulas);
    free(p);
}
