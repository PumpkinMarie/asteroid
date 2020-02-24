#include "Bullet.hh"
#include <utility>

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
    std::cout<<direction_<<std::endl;
    float c = cos( direction_* M_PI / 180 );
    float s = -sin( direction_* M_PI / 180 );
    std::cout<<c<<std::endl;
    std::cout<<s<<std::endl;

    data_.x += c * 2;
    data_.y += s * 2;
    
}

int Bullet::getTime() const {return time_;}

void Bullet::render_bullet(SDL_Renderer* renderer){

    SDL_RenderFillRect(renderer,&data_);
}