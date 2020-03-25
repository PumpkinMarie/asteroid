#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "MovingObject.hh"
#include "utilitaires.hh"

class Asteroids : public MovingObject {
    float radius_;
    SDL_FPoint accel_;
    static const int outerVerticesLen_ =
        10; // nb de points sur le cercle qui forment la météorite
    SDL_FPoint outerVertices_[outerVerticesLen_];
    SDL_FPoint verticesCopy_[outerVerticesLen_]; // copie de l'astéroide pour sa
                                                 // transition aux bords
    SDL_FPoint centerCopie_; // copie du centre
    float variations_[outerVerticesLen_];
    bool dead_ = false;

   public:
    Asteroids(SDL_Window*, float radiusMax = 60.);
    Asteroids(SDL_Window*, float radiusMax, SDL_FPoint center);
    float getRadius();
    void draw() const override;
    void changeData();
    void move() override;
    SDL_Renderer* getRenderer();
    void wrapCoordinates();
    void destruct();
    bool isDead();
};

#endif // ASTEROIDS_H