#include "Asteroids.hh"

#include <iostream>

Asteroids::Asteroids(SDL_Window* window) : window_(window) {
    center_ = {30, 30};
    radius_ = 16;
    speed_  = {1, 2};
    accel_  = {0, 0};
}

void Asteroids::draw() {
    SDL_RenderDrawCircleF(getRenderer(), center_, radius_);
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
    if (center_.x < 0.) {
        res.x = center_.x + (float)width;
    }
    if (center_.x >= (float)width) {
        res.x = center_.x - (float)width;
    }
    if (center_.y < 0.) {
        res.y = center_.y + (float)height;
    }
    if (center_.y >= (float)height) {
        res.y = center_.y - (float)height;
    }
    center_ = res;
}
