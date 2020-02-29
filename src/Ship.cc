#include "Ship.hh"

#include <iostream>

#include "utilitaires.hh"

Ship::Ship(SDL_Window* w)
    : window_(
          w) { // fortement simplifié avec passage de la window pour facilité
    /*     data_[0].x = 320;
        data_[0].y = 240;
        data_[1].x = 310;
        data_[1].y = 220;
        data_[2].x = 320;
        data_[2].y = 225;
        data_[3].x = 330;
        data_[3].y = 220;
        data_[4].x = 320;
        data_[4].y = 240;
     */
    center_ = {320, 240};
    speed_  = {0, 0};
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
        sx[i] = sx[i] * 2;
        sy[i] = sy[i] * 2;
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

SDL_FPoint Ship::getcenter()
    const { // renvoit le centre
    return center_;
}

float Ship::getangle() const { //toujours utile (pour les bullets)
    return angle_;
}

void Ship::move() { // apply speed change to ship
    int width, height;
    SDL_GetWindowSize(window_, &width, &height);
    center_.x += speed_.x;
    center_.y += speed_.y;
    center_.x = wrap(center_.x, width);
    center_.y = wrap(center_.y, height);
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
/*
void Ship::rotation_data(float angle) {
    angle_ = angle_ + angle;
    angle  = angle * M_PI / 180;
    for (int i = 0; i < 5; i++) {
        int xM     = data_[i].x - center_[0];
        int yM     = data_[i].y - center_[1];
        data_[i].x = round(xM * cos(angle) + yM * sin(angle) + center_[0]);
        data_[i].y = round(-xM * sin(angle) + yM * cos(angle) + center_[1]);
    }
    int mid_x  = data_[1].x + (data_[3].x - data_[1].x) / 2;
    int mid_y  = data_[1].y + (data_[3].y - data_[1].y) / 2;
    data_[2].x = mid_x + (data_[0].x - mid_x) / 3;
    data_[2].y = mid_y + (data_[0].y - mid_y) / 3;

    angle_tmp_ = angle_move_;
}*/
/*
void Ship::rotation_render() {
    float angle = angle_ * M_PI / 180 + M_PI / 2;

    data_[0].x = center_[0];
    data_[0].y = center_[1];
    data_[1].x = center_[0] - 10;
    data_[1].y = center_[1] - 20;
    data_[2].x = center_[0];
    data_[2].y = center_[1] - 15;
    data_[3].x = center_[0] + 10;
    data_[3].y = center_[1] - 20;
    data_[4].x = center_[0];
    data_[4].y = center_[1];

    for (int i = 0; i < 5; i++) {
        int xM     = data_[i].x - center_[0];
        int yM     = data_[i].y - center_[1];
        data_[i].x = round(xM * cos(angle) + yM * sin(angle) + center_[0]);
        data_[i].y = round(-xM * sin(angle) + yM * cos(angle) + center_[1]);
    }
    int mid_x  = data_[1].x + (data_[3].x - data_[1].x) / 2;
    int mid_y  = data_[1].y + (data_[3].y - data_[1].y) / 2;
    data_[2].x = mid_x + (data_[0].x - mid_x) / 3;
    data_[2].y = mid_y + (data_[0].y - mid_y) / 3;

    // A revoir version simple mais création de lignes non voulues
    int x = center_[0];
    int y = center_[1];
    if (x < 0)
        for (auto& val : data_) {
            val.x += 640;
        }
    else if (x >= 640)
        for (auto& val : data_) {
            val.x -= 640;
        }
    if (y < 0)
        for (auto& val : data_) {
            val.y += 480;
        }
    else if (x >= 480)
        for (auto& val : data_) {
            val.x -= 480;
        }
}
*/
void Ship::change_speed(float vitesse) {
    // speed_+= vitesse*(1 - (angle_ - angle_move_));
    speed_.x += sin(angle_) * vitesse;
    speed_.y += -cos(angle_) * vitesse;
    move();
}

bool Ship::onCollision(Asteroids a){
    float mx[3]            = {0.0f, -2.5f, +2.5f};
    float my[3]            = {-5.5f, +2.5f, +2.5f};
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
        if (PointdansCercle(sx[i],sy[i],a.getCenter(), a.getRadius()))
            return true;
    }
    return false; 
}
