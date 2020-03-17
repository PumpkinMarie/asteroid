#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <SDL.h>

#include <cmath>

class MovingObject {
    /*SDL_Window* const window_;
    SDL_FPoint center_;
    SDL_FPoint speed_;
    float angle_;
*/
   public:
    SDL_FPoint getCenter();
};

#endif // MOVINGOBJECT_H