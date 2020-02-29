#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#include <cmath>
#include <iostream>

#include "Ship.hh"

class Bullet {
   private:
    SDL_FPoint source_; //origine du tir
    SDL_FRect data_; //position et taille du tir
    SDL_FPoint speed_; //angle et rapidité de déplacement du tir
    int time_; //temps restant avant disparition

   public:
    Bullet(Ship ship);
    void move_bullet();
    int getTime() const;
    void render_bullet(SDL_Renderer* renderer);
    bool onCollision(Asteroids a);

};

#endif // BULLET_H