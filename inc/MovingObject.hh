#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <SDL.h>

#include <cmath>

class MovingObject {
   protected:
    SDL_FPoint center_;
    SDL_Window* window_;
    SDL_FPoint speed_;
    // float angle_;

   public:
    SDL_FPoint getCenter() const {
        return center_;
    };
    virtual void draw() const = 0;
    virtual void move()       = 0;
};

#endif // MOVINGOBJECT_H