#include "Bullet.hh"
#include <utility>
#include "utilitaires.hh"

Bullet::Bullet(Ship ship){
    source_ = ship.getdatafirst();
    direction_ = ship.getangle();
    time_ = 100;
    data_.x = source_.x;
    data_.y = source_.y;
    data_.h = 5;
    data_.w = 5;
}

void Bullet::move_bullet(){
    time_--;

    float c = cos( direction_* M_PI / 180 );
    float s = -sin( direction_* M_PI / 180 );

    data_.x += c * 2;
    data_.y += s * 2;
    
    SDL_Point p;
    p.x = data_.x;
    p.y = data_.y;
    p = Out_of_Screen(p);

    data_.x = p.x;
    data_.y = p.y;
}

int Bullet::getTime() const {return time_;}

void Bullet::render_bullet(SDL_Renderer* renderer){

    SDL_RenderFillRect(renderer,&data_);
}