#include "Asteroids.hh"

#include <iostream>

#include "random.hh"

Asteroids::Asteroids(
    SDL_Window* window, SDL_FPoint shipCenter, float radiusMax) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int side = getRandom(0, 3);
    SDL_FPoint place;
    if (side == 0) { // south
        place.x = getRandom(shipCenter.x + Asteroids::RADIUS_MAX * 2,
            static_cast<float>(width));
        place.y = getRandom(0.0f, static_cast<float>(height));
    } else if (side == 1) { // north
        place.x = getRandom(0.0f, shipCenter.x - Asteroids::RADIUS_MAX * 2);
        place.y = getRandom(0.0f, static_cast<float>(height));
    } else if (side == 2) { // est
        place.x = getRandom(0.0f, static_cast<float>(width));
        place.y = getRandom(shipCenter.y + Asteroids::RADIUS_MAX * 2,
            static_cast<float>(height));
    } else if (side == 3) { // west
        place.x = getRandom(0.0f, static_cast<float>(width));
        place.y = getRandom(0.0f, shipCenter.y - Asteroids::RADIUS_MAX * 2);
    }
    *this = Asteroids(window, radiusMax, place);
}

Asteroids::Asteroids(SDL_Window* window, float radiusMax, SDL_FPoint center) {
    window_      = window;
    float speedx = getRandom(1.0f, 3.0f);
    float speedy = getRandom(1.0f, 3.0f);
    // on vérifie que l'astéroide n'est pas à l'arrêt
    if (speedx - 1 == 0 && speedy - 1 == 0)
        speedx = 2;
    speed_ = {speedx - 1, speedy - 1};
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    center_.x = center.x;
    center_.y = center.y;
    radius_   = getRandom(10.f, radiusMax);

    centerCopie_ = center_;

    for (int i = 0; i < OUTER_VERTICES_LEN; i += 2) {
        variations_[i]     = radius_;
        variations_[i + 1] = getRandom(0.0f, radius_ + radius_ / 3);
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
    for (int i = 0; i < OUTER_VERTICES_LEN; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(renderer,
            outerVertices_[i % OUTER_VERTICES_LEN].x,
            outerVertices_[i % OUTER_VERTICES_LEN].y,
            outerVertices_[j % OUTER_VERTICES_LEN].x,
            outerVertices_[j % OUTER_VERTICES_LEN].y);
        SDL_RenderDrawLineF(renderer,
            verticesCopy_[i % OUTER_VERTICES_LEN].x,
            verticesCopy_[i % OUTER_VERTICES_LEN].y,
            verticesCopy_[j % OUTER_VERTICES_LEN].x,
            verticesCopy_[j % OUTER_VERTICES_LEN].y);
    }
}

// init de points aléatoires formant l'enveloppe convexe de l'astéroide en fct
// du rayon
void Asteroids::changeData() {
    for (int i = 0; i < OUTER_VERTICES_LEN; i++) {
        float angle       = i * 2 * M_PI / OUTER_VERTICES_LEN;
        float cosA        = std::cos(angle) * variations_[i];
        float sinA        = std::sin(angle) * variations_[i];
        outerVertices_[i] = {cosA + center_.x, sinA + center_.y};
        verticesCopy_[i]  = {cosA + centerCopie_.x, sinA + centerCopie_.y};
    }
}

void Asteroids::wrapCoordinates() {
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    centerCopie_   = center_;
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
    changeData();
}
