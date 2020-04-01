#include "Asteroids.hh"

#include <iostream>

#include "random.hh"

Asteroids::Asteroids(SDL_Window* window, float radiusMax) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    *this = Asteroids(window,
        radiusMax,
        {getRandom(0.0f, static_cast<float>(width)),
            getRandom(0.0f, static_cast<float>(height))});
}

Asteroids::Asteroids(SDL_Window* window, float radiusMax, SDL_FPoint center) {
    window_      = window;
    float speedx = rand() % 3;
    float speedy = rand() % 3;
    // on vérifie que l'astéroide n'est pas à l'arrêt
    if (speedx - 1 == 0 && speedy - 1 == 0)
        speedx = 2;
    speed_ = {speedx - 1, speedy - 1};
    accel_ = {0, 0};
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    center_.x = center.x;
    center_.y = center.y;
    radius_   = rand() % int(radiusMax) + 10;

    centerCopie_ = center_;

    for (int i = 0; i < outerVerticesLen_; i += 2) {
        variations_[i]     = radius_;
        variations_[i + 1] = rand() % int(radius_) + radius_ / 3;
    }

    changeData();
}

float Asteroids::getRadius() {
    return radius_;
}

void Asteroids::destruct() {
    dead_ = true;
}

bool Asteroids::isDead() {
    return dead_;
}

void Asteroids::draw() const {
    SDL_Renderer* renderer = SDL_GetRenderer(window_);
    for (int i = 0; i < outerVerticesLen_; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(renderer,
            outerVertices_[i % outerVerticesLen_].x,
            outerVertices_[i % outerVerticesLen_].y,
            outerVertices_[j % outerVerticesLen_].x,
            outerVertices_[j % outerVerticesLen_].y);
        SDL_RenderDrawLineF(renderer,
            verticesCopy_[i % outerVerticesLen_].x,
            verticesCopy_[i % outerVerticesLen_].y,
            verticesCopy_[j % outerVerticesLen_].x,
            verticesCopy_[j % outerVerticesLen_].y);
    }
}

// init de points aléatoires formant l'enveloppe convexe de l'astéroide en fct
// du rayon
void Asteroids::changeData() {
    for (int i = 0; i < outerVerticesLen_; i++) {
        float angle       = i * 2 * M_PI / outerVerticesLen_;
        float cosA        = float(std::cos(angle)) * variations_[i];
        float sinA        = float(sin(angle)) * variations_[i];
        outerVertices_[i] = {cosA + center_.x, sinA + center_.y};
        verticesCopy_[i]  = {cosA + centerCopie_.x, sinA + centerCopie_.y};
    }
}

void Asteroids::move() {
    center_.x += speed_.x;
    center_.y += speed_.y;
    centerCopie_ = center_;
    speed_.x += accel_.x;
    speed_.y += accel_.y;
    wrapCoordinates();
    changeData();
}

SDL_Renderer* Asteroids::getRenderer() {
    return SDL_GetRenderer(window_);
}

void Asteroids::wrapCoordinates() {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);

    SDL_FPoint res = {center_.x, center_.y};
    res.x          = wrap(center_.x, width);
    res.y          = wrap(center_.y, height);
    if (res.x != center_.x && res.y != center_.y)
        centerCopie_ = center_;
    center_ = res;

    for (auto& vertex : outerVertices_) {
        res.x = wrap(vertex.x, width);
        res.y = wrap(vertex.y, height);
        if (res.x > vertex.x) {
            centerCopie_.x += width;
        } else if (res.x < vertex.x) {
            centerCopie_.x -= width;
        }
        if (res.y > vertex.y) {
            centerCopie_.y += height;
        } else if (res.y < vertex.y) {
            centerCopie_.y -= height;
        }
        vertex = res;
    }
}
