#include "Cursor.hh"
#include <iostream>

Cursor::Cursor(){
    
    data_[0].x = 320;
    data_[0].y = 240;
    data_[1].x = 310;
    data_[1].y = 220;
    data_[2].x = 320;
    data_[2].y = 220;
    data_[3].x = 330;
    data_[3].y = 220;
    data_[4].x = 320;
    data_[4].y = 240;

    destination.x = 0;
    destination.y = 5;

    centre_.x = 320;
    centre_.y = 240;

    angle_ = 0;
}


void Cursor::drawdata(SDL_Renderer* renderer) const{
    SDL_RenderDrawLines(renderer,data_,5);
}

void Cursor::move(int direction){
    for(int i=0;i<5;i++){
        switch (direction)
        {
        case 1:
            data_[i].x +=5*destination.x;
            data_[i].y +=5*destination.y;
            break;
        case 2:
            data_[i].x -=5*destination.x;
            data_[i].y -=5*destination.y;
            break;      
        default:
            break;
        }
    }
}

void Cursor::rotation(int direction){
        switch (direction)
        {
        case 1:
            if (destination.x==5)
                destination.x-=1;
            else
                destination.x+=1;

            angle_+=5;
            break;
        case 2:
            if (destination.y==5 && destination.x==5)
                destination.y-=1;
            else if (destination.y==-5 && destination.x==5)
                destination.x-=1;
            else if (destination.y==5 && destination.x==-5)
                destination.x+=1;
            else if (destination.y==-5 && destination.x==-5)
                destination.y+=1;
            else if (destination.y==5)
                destination.x+=1;
            else if (destination.y==-5)
                destination.x-=1;
            else if (destination.x==5)
                destination.y-=1;
            else
                destination.y+=1;

            angle_-=5;
            break;      
        default:
            break;
        }
    std::cout<<destination.x<<" "<<destination.y<<std::endl;
            rotation_data();
}

void Cursor::rotation_data(){
    /*var xM, yM, x, y;
    angle *= Math.PI / 180;
    xM = M.x - O.x;
    yM = M.y - O.y;
    x = xM * Math.cos (angle) + yM * Math.sin (angle) + O.x;
    y = - xM * Math.sin (angle) + yM * Math.cos (angle) + O.y;
    return ({x:Math.round (x), y:Math.round (y)});*/
    float angle = angle_ * M_PI / 180;
    for(int i=0;i<5;i++){  
        int xM = data_[i].x - centre_.x;
        int yM = data_[i].y - centre_.y;
        data_[i].x = round(xM*cos(angle) + yM*sin(angle) + centre_.x);
        data_[i].y = round(- xM*sin(angle) + yM*cos(angle) + centre_.y);
    }
    angle_ = 0;
    std::cout<<data_[2].x<<" "<<data_[2].y<<std::endl;
}
