#include "Ship.hh"

#include <iostream>

#include "utilitaires.hh"

Ship::Ship(SDL_Window*
        w) { // fortement simplifié avec passage de la window pour facilité
    window_ = w;
    placeCenter();
}

float Ship::getAngle() const {
    return angle_;
}

void Ship::placeCenter() {
    int width, height;
    SDL_GetWindowSize(window_, &width, &height);
    center_ = {width / 2, height / 2};
    speed_  = {0, 0};
    accel_  = {0, 0};
    angle_  = 0;
}

void Ship::draw()
    const { // transformations à récupérer pour les autres objets ça marche bien
    SDL_Renderer* renderer = SDL_GetRenderer(window_);
    float mx[3]            = {0.0f, -2.5f, +2.5f};
    float my[3]            = {-5.5f, +2.5f, +2.5f};
    float sx[3];
    float sy[3];

    // rotate
    for (int i = 0; i < 3; i++) {
        sx[i] = mx[i] * cosf(angle_) - my[i] * sinf(angle_);
        sy[i] = mx[i] * sinf(angle_) + my[i] * cosf(angle_);
    }
    // scale
    for (int i = 0; i < 3; i++) {
        sx[i] = sx[i] * 3;
        sy[i] = sy[i] * 3;
    }
    // translate
    for (int i = 0; i < 3; i++) {
        sx[i] += center_.x;
        sy[i] += center_.y;
    }
    // draw
    for (int i = 0; i < 4; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(
            renderer, sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
    }
}

void Ship::rotation(int direction) {
    switch (direction) {
        case 1:
            angle_ += M_PI / 23; // environ pi sur 6
            break;
        case 2:
            angle_ -= M_PI / 23;
            break;
        default:
            break;
    }
    // rotation_data(angle);
}

void Ship::changeSpeed(float vitesse) {
    // speed_+= vitesse*(1 - (angle_ - angle_move_));
    speed_.x += sin(angle_) * vitesse;
    speed_.y += -cos(angle_) * vitesse;
    move();
}

bool Ship::onCollision(Asteroids a) {
    float mx[3] = {0.0f, -2.5f, +2.5f};
    float my[3] = {-5.5f, +2.5f, +2.5f};
    float sx[3];
    float sy[3];

    for (int i = 0; i < 3; i++) {
        sx[i] = mx[i] * cosf(angle_) - my[i] * sinf(angle_);
        sy[i] = mx[i] * sinf(angle_) + my[i] * cosf(angle_);
    }
    for (int i = 0; i < 3; i++) {
        sx[i] = sx[i] * 2;
        sy[i] = sy[i] * 2;
    }
    for (int i = 0; i < 3; i++) {
        sx[i] += center_.x;
        sy[i] += center_.y;
    }

    for (int i = 0; i < 3; i++) {
        if (PointdansCercle(sx[i], sy[i], a.getCenter(), a.getRadius()))
            return true;
    }
    return false;
}
