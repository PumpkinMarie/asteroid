#include "Asteroids.hh"

#include <iostream>

Asteroids::Asteroids() {
    // srand (time(NULL));
    center_[0] = rand() % 640;
    center_[1] = rand() % 480;

    rayon_ = rand() % 20 + 5;

    changeData();

    angle_ = rand() % 360;

    speed_ = 1;
}

void Asteroids::drawdata(SDL_Renderer* renderer) const {
    SDL_RenderDrawLines(renderer, data_, 5);
}

void Asteroids::changeData() {
    data_[0].x = center_[0] + rayon_;
    data_[0].y = center_[1];
    data_[1].x = center_[0];
    data_[1].y = center_[1] - rayon_;
    data_[2].x = center_[0] - rayon_;
    data_[2].y = center_[1];
    data_[3].x = center_[0];
    data_[3].y = center_[1] + rayon_;
    data_[4].x = center_[0] + rayon_;
    data_[4].y = center_[1];
}

float Asteroids::getangle() const {
    return angle_;
}

void Asteroids::move() {
    float c = cos(angle_ * M_PI / 180);
    float s = sin(angle_ * M_PI / 180);

    center_[0] += c * speed_;
    center_[1] -= s * speed_;

    changeData();
}
