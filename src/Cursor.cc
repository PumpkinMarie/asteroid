#include "Cursor.hh"

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

    destination.x = 0;
    destination.y = 1;
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

    for(int i=0;i<5;i++){
        switch (direction)
        {
        case 1:
            data_[i].x -=5;
            data_[i].y -=5;
            break;
        case 2:
            data_[i].y +=5;
            break;      
        default:
            break;
        }
    }
}

