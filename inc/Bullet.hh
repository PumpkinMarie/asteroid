#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#include <cmath>
#include <iostream>

#include "Ship.hh"

class Bullet {
   private:
    SDL_Point source_;
    SDL_Rect data_;
    float direction_;
    int time_;

   public:
    Bullet(Ship ship);
    void move_bullet();
    int getTime() const;
    void render_bullet(SDL_Renderer* renderer);
};

#endif // BULLET_H