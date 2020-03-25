#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include <cmath>
#include <string>

#include "utilitaires.hh"

class Game {
    SDL_Window* const window_;
    int lives_      = 6;
    long int score_ = 235344565;

   public:
    Game(SDL_Window*);
    int getLives() const;
    void lostLife();
    void drawLives() const;
    void drawScore() const;
};

#endif // GAME_H