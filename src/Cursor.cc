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

    destination[0] = 0;
    destination[1] = 1;
}


void Cursor::drawdata(SDL_Renderer* renderer) const{
    SDL_RenderDrawLines(renderer,data_,5);
}

void Cursor::move(int direction){
    for(int i=0;i<5;i++){
        switch (direction)
        {
        case 1:
            data_[i].x +=5*destination[0];
            data_[i].y +=5*destination[1];
            break;
        case 2:
            data_[i].x -=5*destination[0];
            data_[i].y -=5*destination[1];
            break;      
        default:
            break;
        }
    }
}

void Cursor::rotation(int direction){
    std::cout<<destination[0]<<" "<<destination[1]<<std::endl;
    for(int i=0;i<5;i++){
        switch (direction)
        {
        case 1:
            if (destination[1]==1)
                destination[0]-=0.1;
            else
                destination[0]+=0.1;
            break;
        case 2:
            if (destination[1]==1)
                destination[0]+=0.1;
            else
                destination[0]-=0.1;
            
            break;      
        default:
            break;
        }
    }
}

