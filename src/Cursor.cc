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
}


void Cursor::drawdata(SDL_Renderer* renderer) const{
    SDL_RenderDrawLines(renderer,data_,5);
}
