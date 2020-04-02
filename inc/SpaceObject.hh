#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <SDL.h>

#include <cmath>

class SpaceObject {
   protected:
    SDL_Window* window_;
    SDL_FPoint center_;
    SDL_FPoint speed_;
    SDL_FPoint accel_;

   public:
    SDL_Renderer* getRenderer() const;
    SDL_FPoint getSpeed() const;
    SDL_FPoint getCenter() const;
    SDL_FPoint getAccel() const;
    virtual void draw() const = 0;
    void move();
};

#endif // SPACEOBJECT_H