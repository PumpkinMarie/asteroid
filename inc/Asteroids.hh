#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "utilitaires.hh"

class Asteroids {
    SDL_Window* const window_;
    SDL_FPoint center_;
    float radius_;
    SDL_FPoint speed_;
    SDL_FPoint accel_;

   public:
    Asteroids(SDL_Window*);
    void draw();
    void move();
    SDL_Renderer* getRenderer();
    void wrapCoordinates();
};

#endif // ASTEROIDS_H