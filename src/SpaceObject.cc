#include "SpaceObject.hh"

#include "utilitaires.hh"

SDL_Renderer* SpaceObject::getRenderer() const {
    return SDL_GetRenderer(window_);
}

SDL_Window* SpaceObject::getWindow() const {
    return window_;
}

SDL_FPoint SpaceObject::getSpeed() const {
    return speed_;
}

SDL_FPoint SpaceObject::getCenter() const {
    return center_;
}
SDL_FPoint SpaceObject::getAccel() const {
    return accel_;
}

void SpaceObject::move() { // apply speed change to ship
    int width, height;
    SDL_GetWindowSize(window_, &width, &height);
    center_.x += speed_.x;
    center_.y += speed_.y;
    center_.x = wrap(center_.x, width);
    center_.y = wrap(center_.y, height);
    speed_.x += accel_.y;
    speed_.y += accel_.y;
}
