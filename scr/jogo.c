#include "jogo.h"
#include "terminal.h"
#include "defines.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void atirar(EstadoJogo *jogo) {
    for (int i = 0; i < MAX_PROJETEIS; i++) {
        if (!jogo->projeteis[i].ativo) {
            jogo->projeteis[i].x = jogo->carro.x;
            jogo->projeteis[i].y = ALTURA - 2;
            jogo->projeteis[i].ativo = 1;
            break;
        }
    }
}

void iniciar_jogo(EstadoJogo *jogo, const char *nome) {
    jogo->pista = criar_pista(ALTURA, LARGURA);
    if (!jogo->pista) {
        jogo->jogo_acabou = 1;
        return;
    }
    jogo->carro.x = LARGURA / 2;
    jogo->jogo_acabou = 0;
    jogo->pontuacao = 0;
    jogo->atraso = ATRASO_INICIAL;
    jogo->probabilidade_obstaculo = PROB_OBSTACULO_INICIAL;
    jogo->chuva_x_ativa = 0;
    jogo->duracao_chuva_x = 0;
    jogo->tick_chuva = 0;
    strncpy(jogo->nome_jogador, nome, MAX_NOME - 1);
    jogo->nome_jogador[MAX_NOME - 1] = '\0';
    for (int i = 0; i < MAX_PROJETEIS; i++) {
        jogo->projeteis[i].ativo = 0;
    }
}

void liberar_jogo(EstadoJogo *jogo) {
    liberar_pista(jogo->pista);
}

void desenhar_jogo(EstadoJogo *jogo) {
    terminal_ir_topo_esquerda();
    Pista *p = jogo->pista;

    // Desenha a borda superior
    terminal_definir_cor(COR_CIANO); printf("+");
    for (int j = 0; j < p->largura; j++) printf("-");
    printf("+\n");

    // Desenha as células da pista e o carro
    for (int i = 0; i < p->altura; i++) {
        terminal_definir_cor(COR_CIANO); printf("|");
        terminal_definir_cor(COR_RESET);
        for (int j = 0; j < p->largura; j++) {
            char ch = CELULA_VAZIA;
            TerminalCor cor = COR_RESET;
            int proj = 0;

            for(int k = 0; k < MAX_PROJETEIS; k++) {
                if (jogo->projeteis[k].ativo && i == jogo->projeteis[k].y && j == jogo->projeteis[k].x) {
                    ch = EXIBICAO_PROJETIL; cor = COR_MAGENTA; proj = 1; break;
                }
            }
            if (!proj) {
                if (i == p->altura - 1 && j == jogo->carro.x) {
                    ch = EXIBICAO_CARRO; cor = COR_AMARELO;
                } else if (p->celulas[i][j] == CELULA_OBSTACULO) {
                    ch = EXIBICAO_OBSTACULO; cor = COR_VERMELHO;
                }
            }
            terminal_definir_cor(cor); printf("%c", ch); terminal_definir_cor(COR_RESET);
        }
        terminal_definir_cor(COR_CIANO); printf("|\n");
    }

    // Desenha a borda inferior da pista
    terminal_definir_cor(COR_CIANO); printf("+");
    for (int j = 0; j < p->largura; j++) printf("-");
    printf("+\n");

    // Exibe a pontuação e o nome do jogador abaixo da pista
    terminal_definir_cor(COR_BRANCO); printf("Jogador: ");
    terminal_definir_cor(COR_AMARELO); printf("%s", jogo->nome_jogador);
    terminal_definir_cor(COR_BRANCO); printf(" | Pontos: ");
    terminal_definir_cor(COR_VERDE); printf("%d", jogo->pontuacao);
    terminal_definir_cor(COR_RESET); // Reseta a cor
    printf("\n"); // Adiciona uma nova linha para melhor espaçamento

    fflush(stdout);
}

void rolar_pista(EstadoJogo *jogo) {
    Pista *p = jogo->pista;
    for (int i = p->altura - 1; i > 0; i--) {
        memcpy(p->celulas[i], p->celulas[i - 1], p->largura * sizeof(char));
    }

    if (jogo->chuva_x_ativa) {
        jogo->tick_chuva++;
        int gerarX = (jogo->tick_chuva % 2 != 0);
        for (int j = 0; j < p->largura; j++) {
            p->celulas[0][j] = gerarX ? CELULA_OBSTACULO : CELULA_VAZIA;
        }
        jogo->duracao_chuva_x--;
        if (jogo->duracao_chuva_x <= 0) {
            jogo->chuva_x_ativa = 0;
        }
    } else {
        for (int j = 0; j < p->largura; j++) {
            p->celulas[0][j] = (rand() % 100 < jogo->probabilidade_obstaculo) ? CELULA_OBSTACULO : CELULA_VAZIA;
        }
    }
}

void verificar_colisao(EstadoJogo *jogo) {
    if (jogo->pista->celulas[ALTURA - 1][jogo->carro.x] == CELULA_OBSTACULO) {
        jogo->jogo_acabou = 1;
    }
}

void atualizar_projetil(EstadoJogo *jogo) {
    for (int i = 0; i < MAX_PROJETEIS; i++) {
        if (jogo->projeteis[i].ativo) {
            jogo->projeteis[i].y--;
            if (jogo->projeteis[i].y >= 0 && jogo->pista->celulas[jogo->projeteis[i].y][jogo->projeteis[i].x] == CELULA_OBSTACULO) {
                jogo->pista->celulas[jogo->projeteis[i].y][jogo->projeteis[i].x] = CELULA_VAZIA;
                jogo->projeteis[i].ativo = 0;
                jogo->pontuacao += PONTOS_PROJETIL; // Pontuação por X atingido
            } else if (jogo->projeteis[i].y < 0) {
                jogo->projeteis[i].ativo = 0;
            }
        }
    }
}

void atualizar_entrada(EstadoJogo *jogo) {
    int ch = terminal_ler_char_noblock();
    if (ch != -1) {
        if ((ch == 'a' || ch == 'A') && jogo->carro.x > 0) jogo->carro.x--;
        else if ((ch == 'd' || ch == 'D') && jogo->carro.x < LARGURA - 1) jogo->carro.x++;
        else if (ch == 's' || ch == 'S') atirar(jogo);
        else if (ch == 'q' || ch == 'Q') jogo->jogo_acabou = 1;
    }
}

void atualizar_eventos(EstadoJogo *jogo, int *nivelAnterior) {
     int nivelAtual = jogo->pontuacao / PONTOS_EVENTO;

     if (nivelAtual > *nivelAnterior && nivelAtual > 0) {
        if (jogo->atraso > 50000) {
             jogo->atraso = (int)(jogo->atraso * 0.90);
        }
        if (jogo->probabilidade_obstaculo < 20) {
            jogo->probabilidade_obstaculo += 1;
        }
        if (!jogo->chuva_x_ativa) {
            jogo->chuva_x_ativa = 1;
            jogo->duracao_chuva_x = CHUVA_X_DURACAO;
            jogo->tick_chuva = 0;
        }
        *nivelAnterior = nivelAtual;
     }
}

void executar_jogo(const char *nome) {
    EstadoJogo jogo;
    int nivelAnterior = 0;

    iniciar_jogo(&jogo, nome);
    if (jogo.jogo_acabou) {
        fprintf(stderr, "Falha ao inicializar o jogo.\n");
        return;
    }

    terminal_iniciar();
    terminal_limpar_tela();

    while (!jogo.jogo_acabou) {
        atualizar_entrada(&jogo);
        atualizar_projetil(&jogo);
        rolar_pista(&jogo);
        verificar_colisao(&jogo);

        if (jogo.jogo_acabou) break;

        desenhar_jogo(&jogo);
        terminal_dormir_micros(jogo.atraso);

        // Pontuação agora só por acertos de projétil (linha 'jogo.pontuacao++;' removida daqui)
        atualizar_eventos(&jogo, &nivelAnterior);
    }

    terminal_finalizar();
    terminal_limpar_tela();

    terminal_definir_cor(COR_VERMELHO); printf("\n xxx ");
    terminal_definir_cor(COR_BRANCO_NEGRITO); printf("FIM DE JOGO");
    terminal_definir_cor(COR_VERMELHO); printf(" xxx \n\n");

    terminal_definir_cor(COR_BRANCO); printf("%s, sua pontuacao final: ", jogo.nome_jogador);
    terminal_definir_cor(COR_AMARELO); printf("%d\n\n", jogo.pontuacao);
    terminal_definir_cor(COR_RESET);

    salvar_pontuacao(jogo.nome_jogador, jogo.pontuacao);
    liberar_jogo(&jogo);

    terminal_definir_cor(COR_BRANCO); printf("Pressione ");
    terminal_definir_cor(COR_VERDE); printf("ENTER");
    terminal_definir_cor(COR_BRANCO); printf(" para voltar ao menu...");
    terminal_definir_cor(COR_RESET);
    fflush(stdout);

    terminal_limpar_buffer_entrada();
    while (getchar() != '\n');
}
