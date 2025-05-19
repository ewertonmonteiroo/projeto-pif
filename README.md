# 🎮 **Projeto PIF** 🎮


## 👥 **Equipe**

| Nome                      | GitHub                                                   |
|----------------------------|----------------------------------------------------------|
| Dayanne Cristina Moraes      | [@dayannemoraes](https://github.com/dayannemoraes)                      |
| Ewerton Monteiro de Lima    | [@ewertonmonteiroo](https://github.com/ewertonmonteiroo/)                      |


## 📚 **Disciplina**
**Programação Imperativa e Funcional - 2025.1**

## 🏫 **Instituição**
**CESAR School**

---

## Dependências
Projeto utiliza a biblioteca [CLI-lib](https://github.com/tgfb/cli-lib) (requisito obrigatório)

# Descrição da Mecânica do Jogo Racer

#  Racer - Jogo de Corrida

## 📝 Descrição

Text Racer é um jogo simples em modo texto para terminal, onde o jogador controla um carro representado pela letra `A` que deve evitar obstáculos (`#`) que descem pela pista. O jogo usa interação via teclado (teclas A e D para mover o carro, Q para sair), roda em sistemas Linux/macOS e usa manipulação direta do terminal.

## Funcionalidades

- Pista dinâmica gerada aleatoriamente com obstáculos.
- Controle do carro com o teclado (`A` para esquerda, `D` para direita).
- Sistema de colisão: o jogo termina se o carro colidir com um obstáculo.
- Diminuição gradual do delay para aumentar a velocidade do jogo.
- Terminal em modo raw para leitura imediata de teclas (sem necessidade de pressionar ENTER).
- Código modularizado com funções claras e uso de structs para organizar dados do jogo.

## Estruturas usadas

- `Track`: representa a pista (matriz dinâmica de caracteres).
- `Car`: posição do carro.
- `GameState`: estado geral do jogo, incluindo pista, carro, condição de fim e velocidade.

## Requisitos

- Sistema operacional Linux ou macOS.
- Compilador C compatível (gcc, clang).
- Terminal que suporte escape sequences ANSI.
