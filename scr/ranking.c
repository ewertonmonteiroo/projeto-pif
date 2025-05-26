#include "ranking.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_ranking(const void *a, const void *b) {
    return ((EntradaRanking *)b)->pontuacao - ((EntradaRanking *)a)->pontuacao;
}

void salvar_pontuacao(const char *nome, int pontuacao) {
    FILE *f = fopen(RANKING_FILE, "a");
    if (f) {
        fprintf(f, "%s %d\n", nome, pontuacao);
        fclose(f);
    } else {
        perror("Erro ao salvar ranking");
    }
}

void mostrar_ranking() {
    FILE *f = fopen(RANKING_FILE, "r");
    EntradaRanking ranking[100];
    int count = 0;

    terminal_limpar_tela();
    terminal_ir_topo_esquerda();

    terminal_definir_cor(COR_BRANCO_NEGRITO); printf("--- ");
    terminal_definir_cor(COR_AMARELO); printf("RANKING");
    terminal_definir_cor(COR_BRANCO_NEGRITO); printf(" ---\n\n");
    terminal_definir_cor(COR_RESET);

    if (f) {
        while (count < 100 && fscanf(f, "%s %d", ranking[count].nome, &ranking[count].pontuacao) == 2) {
            count++;
        }
        fclose(f);

        qsort(ranking, count, sizeof(EntradaRanking), comparar_ranking);

        int max_mostrar = count < 10 ? count : 10;
        for (int i = 0; i < max_mostrar; i++) {
            terminal_definir_cor(COR_CIANO); printf("%2d. %-20s ", i + 1, ranking[i].nome);
            terminal_definir_cor(COR_VERDE); printf("%d\n", ranking[i].pontuacao);
            terminal_definir_cor(COR_RESET);
        }

        if (count == 0) printf("Nenhum ranking encontrado.\n");

    } else {
        printf("Nenhum ranking encontrado.\n");
    }

    terminal_definir_cor(COR_BRANCO); printf("\nPressione ");
    terminal_definir_cor(COR_VERDE); printf("ENTER");
    terminal_definir_cor(COR_BRANCO); printf(" para voltar...");
    terminal_definir_cor(COR_RESET);
    fflush(stdout);

    terminal_limpar_buffer_entrada();
    while (getchar() != '\n');
    terminal_limpar_buffer_entrada();
}
