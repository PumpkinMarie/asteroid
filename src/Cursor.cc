#include "Cursor.hh"
#include <iostream>

Cursor::Cursor(){
    
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

    centre_.x = 320;
    centre_.y = 240;

    angle_ = -M_PI/2;
}


void Cursor::drawdata(SDL_Renderer* renderer) const{
    SDL_RenderDrawLines(renderer,data_,5);
}

void Cursor::move(int direction){
    float c = cos( angle_ );
    float s = sin( angle_ );

    switch (direction)
    {
    case 1:
        centre_.x = data_[0].x + c * 5;
        centre_.y = data_[0].y - s * 5;
        fct_du_soir();
        break;
    case 2:
        centre_.x = data_[0].x - c * 5;
        centre_.y = data_[0].y + s * 5;
        fct_du_soir();
        break;      
    default:
        break;
    }
}

void Cursor::rotation(int direction){
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

void Cursor::rotation_data(float angle){

    angle = angle * M_PI / 180;
    angle_ = angle_ + angle;
    for(int i=0;i<5;i++){  
        int xM = data_[i].x - centre_.x;
        int yM = data_[i].y - centre_.y;
        data_[i].x = round(xM*cos(angle) + yM*sin(angle) + centre_.x);
        data_[i].y = round(- xM*sin(angle) + yM*cos(angle) + centre_.y);
    }
    int mid_x = data_[1].x + (data_[3].x-data_[1].x)/2;
    int mid_y = data_[1].y + (data_[3].y-data_[1].y)/2;
    data_[2].x = mid_x + (data_[0].x-mid_x)/3;
    data_[2].y = mid_y + (data_[0].y-mid_y)/3;    
}

void Cursor::fct_du_soir(){

    float angle = angle_ + M_PI/2;

    data_[0].x = centre_.x;
    data_[0].y = centre_.y;
    data_[1].x = centre_.x - 10;
    data_[1].y = centre_.y - 20;
    data_[2].x = centre_.x;
    data_[2].y = centre_.y - 15;
    data_[3].x = centre_.x + 10;
    data_[3].y = centre_.y - 20;
    data_[4].x = centre_.x;
    data_[4].y = centre_.y;

    for(int i=0;i<5;i++){  
        int xM = data_[i].x - centre_.x;
        int yM = data_[i].y - centre_.y;
        data_[i].x = round(xM*cos(angle) + yM*sin(angle) + centre_.x);
        data_[i].y = round(- xM*sin(angle) + yM*cos(angle) + centre_.y);
    }
    int mid_x = data_[1].x + (data_[3].x-data_[1].x)/2;
    int mid_y = data_[1].y + (data_[3].y-data_[1].y)/2;
    data_[2].x = mid_x + (data_[0].x-mid_x)/3;
    data_[2].y = mid_y + (data_[0].y-mid_y)/3;   
}
