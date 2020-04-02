#include "Game.hh"

#include "alphabet.hh"

Game::Game(SDL_Window* w) : window_(w) {
}

int Game::getLives() const {
    return lives_;
}

void Game::lostLife() {
    lives_--;
}

void draw(int width, int height, SDL_Window* window) {
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    float mx[3]            = {0.0f, -2.5f, +2.5f};
    float my[3]            = {-5.5f, +2.5f, +2.5f};
    float sx[3];
    float sy[3];

    // rotate
    for (int i = 0; i < 3; i++) {
        sx[i] = mx[i] * cosf(0) - my[i] * sinf(0);
        sy[i] = mx[i] * sinf(0) + my[i] * cosf(0);
    }
    // scale
    for (int i = 0; i < 3; i++) {
        sx[i] = sx[i] * 3;
        sy[i] = sy[i] * 3;
    }
    // translate
    for (int i = 0; i < 3; i++) {
        sx[i] += width;
        sy[i] += height;
    }
    // draw
    for (int i = 0; i < 4; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(
            renderer, sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
    }
}

void Game::drawLives() const {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);

    for (int i = 1; i <= lives_; i++) {
        draw(20 * i, 20, window_);
    }
}

void Game::score(const int points) {
    score_ += points;
}

// fonction d'affichage d'un élément du tableau
void Game::drawascii(int x, int y, int ascii) const {
    // nombre d'éléments décrivant le caractère
    int taille = simplex[ascii][0] * 2;
    // tableau qui va contenir les données du caractères
    float cara[taille];

    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_Renderer* renderer = SDL_GetRenderer(window_);

    // premiers points du tableau en Y
    int max_Y = simplex[ascii][3];
    int min_Y = simplex[ascii][3];

    // on cherche le maximum en Y
    for (int i = 2; i < taille + 2; i += 2) {
        if (simplex[ascii][i + 1] < min_Y && simplex[ascii][i + 1] >= 0)
            min_Y = simplex[ascii][i + 1];
        if (simplex[ascii][i + 1] > max_Y)
            max_Y = simplex[ascii][i + 1];
    }

    // remplit le tableau du caractère et modifie les valeurs en Y pour les
    // inverser (pour les besoins de l'affichage)
    for (int i = 0; i < taille; i += 2) {
        if (simplex[ascii][i + 2] == -1 && simplex[ascii][i + 3] == -1) {
            cara[i]     = -1;
            cara[i + 1] = -1;
        } else {
            cara[i]     = simplex[ascii][i + 2];
            cara[i + 1] = max_Y - (simplex[ascii][i + 3] - min_Y);
        }
    }
    // draw
    for (int i = 0; i < taille - 2; i += 2) {
        if (cara[i + 2] != -1 && cara[i + 3] != -1 && cara[i] != -1 &&
            cara[i + 1] != -1)
            SDL_RenderDrawLineF(renderer,
                cara[i] + x,
                cara[i + 1] + y,
                cara[i + 2] + x,
                cara[i + 3] + y);
    }
}

void Game::drawScore() const {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);

    long int score = score_;
    int chiffre    = score % 10;
    // score max
    if (score > 1000000000)
        score = 1000000000;
    // draw chaque chiffre du score
    do {
        chiffre = score % 10;
        drawascii(width - 20, 10, 48 + chiffre - 32);
        width -= 20;
        score /= 10;
    } while (score != 0);
}
