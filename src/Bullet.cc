#include "Bullet.hh"

#include "Ship.hh"
#include "SpaceObject.hh"

Bullet::Bullet(Ship& ship) {
    SDL_FPoint source = ship.getCenter();
    time_             = 500;
    center_.x         = source.x;
    center_.y =
        source.y - 5.5f; // tir venant de la pointe du vaisseau pas du centre

    float direction        = ship.getAngle();
    SDL_FPoint sourceSpeed = ship.getSpeed();
    speed_.x               = sin(direction) + sourceSpeed.x;
    speed_.y               = -cos(direction) + sourceSpeed.y;
}

void Bullet::moveBullet() {
    time_--;
    move();
}

int Bullet::getTime() const {
    return time_;
}

void Bullet::draw() const {
    SDL_Renderer* rdr = SDL_GetRenderer(window_);
    SDL_RenderSetScale(rdr, 2, 2);
    SDL_RenderDrawPointF(rdr, center_.x, center_.y);
    SDL_RenderSetScale(rdr, 2, 2);
}

bool Bullet::onCollision(Asteroids a) {
    if (PointdansCercle(center_.x, center_.y, a.getCenter(), a.getRadius()))
        return true;
    if (PointdansCercle(center_.x + 5, center_.y, a.getCenter(), a.getRadius()))
        return true;
    if (PointdansCercle(center_.x, center_.y + 5, a.getCenter(), a.getRadius()))
        return true;
    if (PointdansCercle(
            center_.x + 5, center_.y + 5, a.getCenter(), a.getRadius()))
        return true;
    return false;
}