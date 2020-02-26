#include "Bullet.hh"

#include <utility>

#include "utilitaires.hh"

Bullet::Bullet(Ship ship) {
    source_    = ship.getcenter();
    time_      = 500;
    data_.x    = source_.x;
    data_.y    = source_.y-5.5f; //tir venant de la pointe du vaisseau pas du centre
    data_.h    = 5;
    data_.w    = 5;

    float direction = ship.getangle();
    speed_.x = sin(direction);
    speed_.y = -cos(direction);
    }

void Bullet::move_bullet() {
    time_--;

    data_.x += speed_.x;
    data_.y += speed_.y;

    data_.x = wrap(data_.x, 640);
    data_.y = wrap(data_.y, 480);
}

int Bullet::getTime() const {
    return time_;
}

void Bullet::render_bullet(SDL_Renderer* renderer) {
    SDL_RenderFillRectF(renderer, &data_);
}