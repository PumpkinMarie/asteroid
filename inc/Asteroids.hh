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
    static const int OUTER_VERTICES_LEN =
        10; // nb de points sur le cercle qui forment la météorite
    SDL_FPoint outerVertices_[OUTER_VERTICES_LEN];
    SDL_FPoint verticesCopy_[OUTER_VERTICES_LEN]; // copie de l'astéroide pour
                                                  // sa transition aux bords
    SDL_FPoint centerCopie_;                      // copie du centre
    float variations_[OUTER_VERTICES_LEN];
    bool dead_ = false;

   public:
    constexpr static const float RADIUS_MAX = 60.;
    Asteroids(SDL_Window*, SDL_FPoint shipCenter, float radiusMax = RADIUS_MAX);
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