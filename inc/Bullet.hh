#ifndef BULLET_H
#define BULLET_H

#include "Ship.hh"
#include "SpaceObject.hh"

class Bullet : SpaceObject {
   private:
    int time_; // temps restant avant disparition

   public:
    Bullet(Ship &ship);
    void moveBullet();
    int getTime() const;
    void draw() const override;
    bool onCollision(Asteroids a);
};

#endif // BULLET_H