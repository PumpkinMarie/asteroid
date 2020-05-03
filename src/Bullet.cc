#include "Bullet.hh"

#include "Ship.hh"
#include "SpaceObject.hh"

Bullet::Bullet(Ship& ship) {
    window_           = ship.getWindow();
    SDL_FPoint source = ship.getCenter();
    time_             = 500;
    center_.x         = source.x;
    center_.y =
        source.y - 5.5f; // tir venant de la pointe du vaisseau pas du centre
    accel_                 = {0., 0.};
    float direction        = ship.getAngle();
    SDL_FPoint sourceSpeed = ship.getSpeed();
    speed_.x               = std::sin(direction) + sourceSpeed.x;
    speed_.y               = -std::cos(direction) + sourceSpeed.y;
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
    for (int w = 0; w < RADIUS * 2; w++) {
        for (int h = 0; h < RADIUS * 2; h++) {
            int dx = RADIUS - w; // horizontal offset
            int dy = RADIUS - h; // vertical offset
            if ((dx * dx + dy * dy) <= (RADIUS * RADIUS)) {
                SDL_RenderDrawPoint(rdr, center_.x + dx, center_.y + dy);
            }
        }
    }
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