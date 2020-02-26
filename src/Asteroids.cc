#include "Asteroids.hh"

#include <iostream>

Asteroids::Asteroids(SDL_Window* window) : window_(window) {
    center_ = {30, 30};
    radius_ = 50;
    speed_  = {1, 2};
    accel_  = {0, 0};
}

void Asteroids::draw() {
    SDL_RenderDrawCircleF(window_, center_, radius_);
}

void Asteroids::move() {
    center_.x += speed_.x;
    center_.y += speed_.y;
    speed_.x += accel_.x;
    speed_.y += accel_.y;
    wrapCoordinates();
}

SDL_Renderer* Asteroids::getRenderer() {
    return SDL_GetRenderer(window_);
}

void Asteroids::wrapCoordinates() {
    SDL_FPoint res = {center_.x, center_.y};
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    res.x   = wrap(center_.x, width);
    res.y   = wrap(center_.y, height);
    center_ = res;
}
