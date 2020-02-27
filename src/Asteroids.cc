#include "Asteroids.hh"

#include <iostream>

Asteroids::Asteroids(SDL_Window* window) : window_(window) {
    float speedx = rand()%3;
    float speedy = rand()%3;
    if (speedx-1 == 0 && speedy-1 == 0)
        speedx = 2;
    speed_  = {speedx-1, speedy-1};
    accel_  = {0, 0};
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    center_.x = rand()%width;
    center_.y = rand()%height;
    radius_ = rand()%70+10;

    center_tmp = center_;

    changeData();
}

void Asteroids::draw() {
    SDL_Renderer* renderer = SDL_GetRenderer(window_);
    for (int i = 0; i < nb_points_; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(
            renderer, data_[i % nb_points_].x, data_[i % nb_points_].y, data_[j % nb_points_].x, data_[j % nb_points_].y);
        SDL_RenderDrawLineF(
            renderer, data_tmp[i % nb_points_].x, data_tmp[i % nb_points_].y, data_tmp[j % nb_points_].x, data_tmp[j % nb_points_].y);
    }
    //SDL_RenderDrawCircleF(window_, center_, radius_);
}

//init de points aléatoires formant l'enveloppe convexe de l'astéroide en fct du rayon
void Asteroids::changeData() {
    for (int i=0;i<nb_points_;i++){
        data_[i] = {float(cos(i*2*M_PI/nb_points_))*radius_+center_.x,float(sin(i*2*M_PI/nb_points_))*radius_+center_.y};
        data_tmp[i] = {float(cos(i*2*M_PI/nb_points_))*radius_+center_tmp.x,float(sin(i*2*M_PI/nb_points_))*radius_+center_tmp.y};
    }
}

void Asteroids::move() {
    center_.x += speed_.x;
    center_.y += speed_.y;
    center_tmp = center_;
    speed_.x += accel_.x;
    speed_.y += accel_.y;
    wrapCoordinates();
    changeData();
}

SDL_Renderer* Asteroids::getRenderer() {
    return SDL_GetRenderer(window_);
}

void Asteroids::wrapCoordinates() {
    /*SDL_FPoint res = {center_.x, center_.y};
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    res.x   = wrap(center_.x, width);
    res.y   = wrap(center_.y, height);
    center_ = res;*/

    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);

    SDL_FPoint res = {center_.x, center_.y};
        res.x   = wrap(center_.x, width);
        res.y   = wrap(center_.y, height);
        if (res.x != center_.x && res.y!= center_.y)
            center_tmp = center_;
        center_ = res;

    for (int i = 0; i < nb_points_; i++) {

        res.x   = wrap(data_[i].x, width);
        res.y   = wrap(data_[i].y, height);
        if (res.x>data_[i].x){
            center_tmp.x += width;
            break;  
        }
        if (res.x<data_[i].x){
            center_tmp.x -= width;  
            break;  
        }
        if (res.y>data_[i].y){
            center_tmp.y += height;  
            break;  
        }
        if (res.y<data_[i].y){
            center_tmp.y -= height;  
            break;  
        }
        data_[i] = res; 
    }

}
