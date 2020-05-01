#include "Game.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "alphabet.hh"

Game::Game(SDL_Window* w) : window_(w) {
    name_[0] = 65;
    name_[1] = 65;
    name_[2] = 65;
}

void Game::changeCaraPlus() {
    if (name_[name_index_] < 126)
        name_[name_index_]++;
}
void Game::changeCaraMinus() {
    if (name_[name_index_] > 32)
        name_[name_index_]--;
}

void Game::changeNameIndexPlus() {
    if (name_index_ < 2)
        name_index_++;
}
void Game::changeNameIndexMinus() {
    if (name_index_ > 0)
        name_index_--;
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

void Game::drawStartMenu() const {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_Renderer* renderer = SDL_GetRenderer(window_);

    int middleW = width / 2;
    // Push Start
    drawascii(middleW - 100, height / 2, 80 - 32);
    drawascii(middleW - 80, height / 2, 85 - 32);
    drawascii(middleW - 60, height / 2, 83 - 32);
    drawascii(middleW - 40, height / 2, 72 - 32);
    drawascii(middleW - 20, height / 2, 32 - 32);
    drawascii(middleW + 20, height / 2, 83 - 32);
    drawascii(middleW + 40, height / 2, 84 - 32);
    drawascii(middleW + 60, height / 2, 65 - 32);
    drawascii(middleW + 80, height / 2, 82 - 32);
    drawascii(middleW + 100, height / 2, 84 - 32);
}

void Game::drawEndMenu() const {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_Renderer* renderer = SDL_GetRenderer(window_);

    int middleW = width / 2;
    int middleH = height / 2;

    // GAME OVER
    drawascii(middleW - 80, middleH - 50, 71 - 32);
    drawascii(middleW - 60, middleH - 50, 65 - 32);
    drawascii(middleW - 40, middleH - 50, 77 - 32);
    drawascii(middleW - 20, middleH - 50, 69 - 32);
    drawascii(middleW, middleH - 50, 32 - 32);
    drawascii(middleW + 20, middleH - 50, 79 - 32);
    drawascii(middleW + 40, middleH - 50, 86 - 32);
    drawascii(middleW + 60, middleH - 50, 69 - 32);
    drawascii(middleW + 80, middleH - 50, 82 - 32);

    // ENTER YOUR NAME
    drawascii(middleW - 140, middleH + 20, 69 - 32);
    drawascii(middleW - 120, middleH + 20, 78 - 32);
    drawascii(middleW - 100, middleH + 20, 84 - 32);
    drawascii(middleW - 80, middleH + 20, 69 - 32);
    drawascii(middleW - 60, middleH + 20, 82 - 32);
    drawascii(middleW - 40, middleH + 20, 32 - 32);
    drawascii(middleW - 20, middleH + 20, 89 - 32);
    drawascii(middleW, middleH + 20, 79 - 32);
    drawascii(middleW + 20, middleH + 20, 85 - 32);
    drawascii(middleW + 40, middleH + 20, 82 - 32);
    drawascii(middleW + 60, middleH + 20, 32 - 32);
    drawascii(middleW + 80, middleH + 20, 78 - 32);
    drawascii(middleW + 100, middleH + 20, 65 - 32);
    drawascii(middleW + 120, middleH + 20, 77 - 32);
    drawascii(middleW + 140, middleH + 20, 69 - 32);

    // NAME
    drawascii(middleW - 40, middleH + 100, name_[0] - 32);
    drawascii(middleW, middleH + 100, name_[1] - 32);
    drawascii(middleW + 40, middleH + 100, name_[2] - 32);

    // _ _ _ (underscore pour aider le joueur à savoir quelle lettre il modifie)
    int val = 0;
    switch (name_index_) {
        case 0:
            val = -40;
            break;
        case 1:
            val = 0;
            break;
        case 2:
            val = 40;
    }
    drawascii(middleW + val, middleH + 140, 95 - 32);
}

void Game::drawScores() const {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_Renderer* renderer = SDL_GetRenderer(window_);

    int middleW = width / 2;
    int middleH = height / 2;

    // HIGH SCORES
    drawascii(middleW - 140, 40, 'H' - 32);
    drawascii(middleW - 120, 40, 'I' - 32);
    drawascii(middleW - 100, 40, 'G' - 32);
    drawascii(middleW - 80, 40, 'H' - 32);
    drawascii(middleW - 60, 40, ' ' - 32);
    drawascii(middleW - 40, 40, 'S' - 32);
    drawascii(middleW - 20, 40, 'C' - 32);
    drawascii(middleW, 40, 'O' - 32);
    drawascii(middleW + 20, 40, 'R' - 32);
    drawascii(middleW + 40, 40, 'E' - 32);
    drawascii(middleW + 60, 40, 'S' - 32);

    std::ifstream inputFile("scores.dat");
    char line[15]; // 3 for name 1 for colon 10 for score 1 for security
    std::vector<std::pair<std::string, u_int64_t>> records;
    while (inputFile.getline(line, 15)) {
        std::string str(line);
        std::string name(str.substr(0, str.find(':')));
        u_int64_t score;
        std::istringstream(str.substr(str.find(':') + 1)) >> score;
        records.push_back({name, score});
    }
    inputFile.close();
    std::sort(
        records.begin(), records.end(), []<class T>(T a, T b)->bool {
            return a.second > b.second;
        });
    records.resize(10);
    int i = -100;
    for (auto pair : records) {
        int j = 200;
        if (pair.first != "") {
            drawascii(middleW - 80, middleH + i, pair.first[0] - 32);
            drawascii(middleW - 40, middleH + i, pair.first[1] - 32);
            drawascii(middleW + 0, middleH + i, pair.first[2] - 32);

            long int score = pair.second;
            int chiffre    = score % 10;
            // draw chaque chiffre du score
            do {
                chiffre = score % 10;
                drawascii(middleW + j, middleH + i, 48 + chiffre - 32);
                width -= 20;
                score /= 10;
                j -= 20;
            } while (score != 0);
        }
        i += 40;
    }
}

void Game::saveScore() const {
    std::ofstream outputFile("scores.dat", std::ios::app);
    for (auto c : name_) {
        outputFile << c;
    }
    outputFile << ":" << score_ << std::endl;
    outputFile.close();
}