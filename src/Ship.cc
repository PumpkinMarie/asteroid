#include "Ship.hh"
#include <iostream>

Ship::Ship(){
    
    data_[0].x = 320;
    data_[0].y = 240;
    data_[1].x = 310;
    data_[1].y = 220;
    data_[2].x = 320;
    data_[2].y = 225;
    data_[3].x = 330;
    data_[3].y = 220;
    data_[4].x = 320;
    data_[4].y = 240;

    center_[0] = 320;
    center_[1] = 240;

    angle_ = 0;
    angle_move_ = 0;
    speed_ = 0;
}


void Ship::drawdata(SDL_Renderer* renderer) const{
    SDL_RenderDrawLines(renderer,data_,5);
}

void Ship::move(){
    float c = cos( angle_move_* M_PI / 180 );
    float s = sin( angle_move_* M_PI / 180 );

    center_[0] = data_[0].x + c * speed_;
    center_[1] = data_[0].y - s * speed_;
    rotation_render();

}

void Ship::rotation(int direction){
    int angle;
    switch (direction)
    {
    case 1:
        angle = 5;
        break;
    case 2:
        angle = -5;
        break;      
    default:
        break;
    }
    rotation_data(angle);
}

void Ship::rotation_data(float angle){

    angle_ = angle_ + angle;
    angle = angle * M_PI / 180;
    for(int i=0;i<5;i++){  
        int xM = data_[i].x - center_[0];
        int yM = data_[i].y - center_[1];
        data_[i].x = round(xM*cos(angle) + yM*sin(angle) + center_[0]);
        data_[i].y = round(- xM*sin(angle) + yM*cos(angle) + center_[1]);
    }
    int mid_x = data_[1].x + (data_[3].x-data_[1].x)/2;
    int mid_y = data_[1].y + (data_[3].y-data_[1].y)/2;
    data_[2].x = mid_x + (data_[0].x-mid_x)/3;
    data_[2].y = mid_y + (data_[0].y-mid_y)/3;    

    angle_tmp_ = angle_move_;

}

void Ship::rotation_render(){

    float angle = angle_* M_PI / 180 + M_PI/2;

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

    for(int i=0;i<5;i++){  
        int xM = data_[i].x - center_[0];
        int yM = data_[i].y - center_[1];
        data_[i].x = round(xM*cos(angle) + yM*sin(angle) + center_[0]);
        data_[i].y = round(- xM*sin(angle) + yM*cos(angle) + center_[1]);
    }
    int mid_x = data_[1].x + (data_[3].x-data_[1].x)/2;
    int mid_y = data_[1].y + (data_[3].y-data_[1].y)/2;
    data_[2].x = mid_x + (data_[0].x-mid_x)/3;
    data_[2].y = mid_y + (data_[0].y-mid_y)/3;   
}

void Ship::change_speed(int vitesse){
    //speed_+= vitesse*(1 - (angle_ - angle_move_));
    speed_ = vitesse;
    if (angle_move_ != angle_){
        angle_move_ += (angle_ - angle_tmp_)*0.1*speed_;
        std::cout<<angle_<<" "<<angle_move_<< " "<< angle_tmp_<<std::endl;
    }
    move();
}
