#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define CAR 'A'
#define OBSTACLE '#'
#define EMPTY ' '

typedef struct {
    char **cells;
    int width;
    int height;
} Track;

typedef struct {
    int x;
} Car;

typedef struct {
    Track *track;
    Car car;
    int gameOver;
    int delay;
} GameState;

void clearScreen() {
    printf("\033[H\033[J");
}

void enableRawMode(struct termios *orig_termios) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void disableRawMode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
    fcntl(STDIN_FILENO, F_SETFL, 0);
}

Track *createTrack(int height, int width) {
    Track *t = malloc(sizeof(Track));
    t->height = height;
    t->width = width;
    t->cells = malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        t->cells[i] = malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            t->cells[i][j] = EMPTY;
        }
    }
    return t;
}

void freeTrack(Track *t) {
    for (int i = 0; i < t->height; i++) {
        free(t->cells[i]);
    }
    free(t->cells);
    free(t);
}

void initGame(GameState *game) {
    game->track = createTrack(HEIGHT, WIDTH);
    game->car.x = WIDTH / 2;
    game->gameOver = 0;
    game->delay = 250000;
}

void drawGame(GameState *game) {
    clearScreen();
    Track *t = game->track;
    for (int i = 0; i < t->height; i++) {
        for (int j = 0; j < t->width; j++) {
            if (i == t->height - 1 && j == game->car.x)
                putchar(CAR);
            else
                putchar(t->cells[i][j]);
        }
        putchar('\n');
    }
    printf("Controles: A=Esquerda D=Direita Q=Sair\n");
}

void scrollTrack(GameState *game) {
    Track *t = game->track;
    for (int i = t->height - 1; i > 0; i--) {
        for (int j = 0; j < t->width; j++) {
            t->cells[i][j] = t->cells[i-1][j];
        }
    }
    for (int j = 0; j < t->width; j++) {
        t->cells[0][j] = (rand() % 100 < 5) ? OBSTACLE : EMPTY;
    }
}

void checkCollision(GameState *game) {
    if (game->track->cells[game->track->height - 1][game->car.x] == OBSTACLE) {
        game->gameOver = 1;
    }
}

void updateInput(GameState *game) {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        if ((ch == 'a' || ch == 'A') && game->car.x > 0)
            game->car.x--;
        else if ((ch == 'd' || ch == 'D') && game->car.x < game->track->width - 1)
            game->car.x++;
        else if (ch == 'q' || ch == 'Q')
            game->gameOver = 1;
    }
}

void freeGame(GameState *game) {
    freeTrack(game->track);
}

int main() {
    srand(time(NULL));
    struct termios orig_termios;
    GameState game;
    initGame(&game);
    enableRawMode(&orig_termios);

    clearScreen();
    printf("=== Text Racer ===\n");
    printf("Pressione 'a' para mover para esquerda\n");
    printf("Pressione 'd' para mover para direita\n");
    printf("Pressione 'q' para sair\n");
    printf("Pressione ENTER para começar...");
    while (getchar() != '\n') {}

    while (!game.gameOver) {
        scrollTrack(&game);
        checkCollision(&game);
        drawGame(&game);
        updateInput(&game);
        usleep(game.delay);
        if (game.delay > 60000)
            game.delay -= 200;
    }

    disableRawMode(&orig_termios);
    clearScreen();
    printf("=== Game Over ===\n");
    freeGame(&game);
    return 0;
}
