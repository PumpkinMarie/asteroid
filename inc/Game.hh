#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include <cmath>
#include <string>

#include "utilitaires.hh"

class Game {
    SDL_Window* const window_;
    int lives_       = 6;
    u_int64_t score_ = 0;
    u_char name_[3];
    int name_index_ = 0;

   public:
    Game(SDL_Window*);
    int getLives() const;
    void changeCaraPlus();
    void changeCaraMinus();
    void changeNameIndexPlus();
    void changeNameIndexMinus();
    void lostLife();
    void score(const int points);
    void saveScore() const;
    void drawStartMenu() const;
    void drawEndMenu() const;
    void drawScores() const;
    void drawascii(int x, int y, int ascii) const;
    void drawLives() const;
    void drawScore() const;
};

#endif // GAME_H