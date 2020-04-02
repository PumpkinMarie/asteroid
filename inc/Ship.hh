#ifndef SHIP_H
#define SHIP_H

#include <SDL.h>

#include "Asteroids.hh"
#include "SpaceObject.hh"

class Ship : public SpaceObject {
    float angle_;

   public:
    Ship(SDL_Window*);
    float getAngle() const;
    void placeCenter();
    void draw() const override; // dessine les lignes du vaisseau
    void rotation(int direction);
    void changeSpeed(float vitesse);
    bool onCollision(Asteroids a);
};

#endif // SHIP_H