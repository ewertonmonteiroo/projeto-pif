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

Text Racer é um jogo de corrida baseado em texto para terminal, onde o jogador assume o controle de um carro, representado pela letra 'O'. O objetivo é navegar por uma pista em constante movimento, desviando de obstáculos ('X') e, crucialmente, destruindo-os com projéteis ('^') para acumular pontos. O jogo se adapta à sua performance, tornando-se mais rápido e desafiador à medida que sua pontuação cresce.

## Funcionalidades

- Pista Dinâmica: A pista é gerada aleatoriamente a cada nova linha, com obstáculos que descem simulando o movimento.
Controle Preciso: Mova o carro para a esquerda (A/a) ou direita (D/d).
- Sistema de Disparo: Atire projéteis ('^') para cima pressionando S/s.
- Pontuação por Acerto: Marque pontos apenas ao destruir obstáculos ('X') com seus projéteis, recompensando a precisão do tiro.
- Dificuldade Adaptativa: O jogo acelera e a probabilidade de surgimento de obstáculos aumenta conforme você pontua, incluindo eventos especiais como a "Chuva X" de obstáculos.
- Colisão Fatal: O jogo termina imediatamente se seu carro colidir com um obstáculo.
- Ranking de Pontuações: Suas pontuações mais altas são salvas e podem ser visualizadas no menu principal, com os maiores recordes em destaque.
- Exibição Otimizada: Sua pontuação e nome de jogador são exibidos de forma clara abaixo da pista, mantendo a área de jogo principal limpa.
- Interação em Tempo Real: O terminal é configurado para ler as teclas imediatamente (modo raw), garantindo uma jogabilidade fluida sem a necessidade de ENTER.
- Código Modularizado: O projeto é bem organizado, utilizando structs e funções separadas em arquivos (.h e .c) para gerenciar a lógica da pista, carro, projéteis e o estado geral do jogo.

## 📈 Sistema de Pontuação e Ranking

A pontuação no Text Racer é diretamente ligada à sua precisão e habilidade. Você ganha pontos exclusivamente ao destruir obstáculos ('X') com seus projéteis ('^'). Isso significa que cada tiro certeiro recompensa sua estratégia. Conforme você acumula pontos, a dificuldade do jogo aumenta progressivamente, com a pista acelerando e novos desafios surgindo. Ao final de cada partida, sua pontuação é registrada no ranking global, permitindo que você veja e dispute pelas maiores pontuações.

## 🏆 Pontuação e Classificação

Em "Text Racer", a pontuação é mais do que um número – é um reflexo da sua maestria. Você pontua apenas acertando e destruindo obstáculos ('X') com seus projéteis ('^'), o que exige foco e mira precisa. Essa progressão de pontos não só eleva seu recorde, mas também impulsiona a dificuldade do jogo, introduzindo maior velocidade e mais obstáculos para testar seus limites. Todas as suas pontuações finais são salvas e exibidas no ranking do jogo, incentivando a competição e a busca pelo topo da lista entre os pilotos mais habilidosos.

## Estruturas usadas

- Pista: Representa a matriz dinâmica de caracteres que forma a pista e seus elementos.
- Carro: Armazena a posição horizontal do carro do jogador.
- Projetil: Gerencia a posição e o estado (ativo/inativo) de cada projétil disparado.
- EstadoJogo: Contém todas as informações essenciais do jogo em um único local, como a pista, carro, projéteis, pontuação, velocidade do jogo e parâmetros de dificuldade.

## Requisitos

- Sistema operacional Linux ou macOS.
- Compilador C compatível (gcc, clang).
- Terminal que suporte escape sequences ANSI.
