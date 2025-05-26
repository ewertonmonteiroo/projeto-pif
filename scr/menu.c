#include "menu.h"
#include "terminal.h"
#include "jogo.h"
#include "ranking.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static void pedir_nome(char *nome) {
    terminal_limpar_tela();
    terminal_ir_topo_esquerda();
    terminal_definir_cor(COR_BRANCO); printf("Digite seu nome (max %d caracteres): ", MAX_NOME - 1);
    terminal_definir_cor(COR_VERDE);
    fflush(stdout);

    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    if (strlen(nome) == 0) {
        strcpy(nome, "Jogador");
    }
    terminal_definir_cor(COR_RESET);
}

void mostrar_menu_principal() {
    char escolha;
    char nome_jogador[MAX_NOME];
    struct termios term_orig, term_raw;

    tcgetattr(STDIN_FILENO, &term_orig);
    term_raw = term_orig;
    term_raw.c_lflag &= ~(ICANON | ECHO);

    while(1) {
        tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
        terminal_limpar_tela();
        terminal_ir_topo_esquerda();

        terminal_definir_cor(COR_BRANCO_NEGRITO); printf("=== ");
        terminal_definir_cor(COR_AMARELO); printf("CORRIDA DE TEXTO");
        terminal_definir_cor(COR_BRANCO_NEGRITO); printf(" ===\n\n");
        terminal_definir_cor(COR_RESET);

        terminal_definir_cor(COR_VERDE); printf(" 1. ");
        terminal_definir_cor(COR_BRANCO); printf("Comecar Jogo\n");

        terminal_definir_cor(COR_CIANO); printf(" 2. ");
        terminal_definir_cor(COR_BRANCO); printf("Ver Ranking\n");

        terminal_definir_cor(COR_VERMELHO); printf(" 3. ");
        terminal_definir_cor(COR_BRANCO); printf("Sair\n\n");

        terminal_definir_cor(COR_AMARELO); printf("Escolha uma opcao: ");
        terminal_definir_cor(COR_RESET);
        fflush(stdout);

        tcsetattr(STDIN_FILENO, TCSANOW, &term_raw);
        read(STDIN_FILENO, &escolha, 1);
        tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);

        switch(escolha) {
            case '1':
                pedir_nome(nome_jogador);
                executar_jogo(nome_jogador);
                break;
            case '2':
                mostrar_ranking();
                break;
            case '3':
                terminal_limpar_tela();
                printf("Ate mais!\n");
                return;
            default:
                printf("\nOpcao invalida! Pressione ENTER...");
                fflush(stdout);
                while(getchar() != '\n');
        }
    }
}
