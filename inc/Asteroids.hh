#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "utilitaires.hh"

class Asteroids {
    SDL_Window* window_;
    SDL_FPoint center_;
    float radius_;
    SDL_FPoint speed_;
    SDL_FPoint accel_;
    int nb_points_ = 10; //nb de points sur le cercle qui forment la météorite
    SDL_FPoint data_[10]; 
    SDL_FPoint data_copie[10]; //copie de l'astéroide pour sa transition aux bords
    SDL_FPoint center_copie; //copie du centre
    float variations_[10]; 
    bool dead_=false;

   public:
    Asteroids(SDL_Window*);
    Asteroids(SDL_Window*,float radiusMax,SDL_FPoint center);
    SDL_FPoint getCenter();
    float getRadius();
    void draw();
    void changeData();
    void move();
    SDL_Renderer* getRenderer();
    void wrapCoordinates();
    void destruct();
    bool isDead();
};

#endif // ASTEROIDS_H