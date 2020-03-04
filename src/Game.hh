#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
    SDL_Window* const window_;
    int lives_ = 6;

    public:
        Game(SDL_Window*);
        int getLives() const;
        void lostLife();
        void drawLives() const;

};

#endif // GAME_H