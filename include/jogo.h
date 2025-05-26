#ifndef JOGO_H
#define JOGO_H

#include "pista.h"
#include "defines.h"

typedef struct {
    int x;
} Carro;

typedef struct {
    int x;
    int y;
    int ativo;
} Projetil;

typedef struct {
    Pista *pista;
    Carro carro;
    Projetil projeteis[MAX_PROJETEIS];
    int jogo_acabou;
    int pontuacao;
    int atraso;
    char nome_jogador[MAX_NOME];
    int probabilidade_obstaculo;
    int chuva_x_ativa;
    int duracao_chuva_x;
    int tick_chuva;
} EstadoJogo;

void iniciar_jogo(EstadoJogo *jogo, const char *nome);
void liberar_jogo(EstadoJogo *jogo);
void desenhar_jogo(EstadoJogo *jogo);
void rolar_pista(EstadoJogo *jogo);
void verificar_colisao(EstadoJogo *jogo);
void atualizar_projetil(EstadoJogo *jogo);
void atualizar_entrada(EstadoJogo *jogo);
void atualizar_eventos(EstadoJogo *jogo, int *nivelAnterior);
void executar_jogo(const char *nome);

#endif
