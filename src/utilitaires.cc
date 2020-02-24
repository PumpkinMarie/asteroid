#include "utilitaires.hh"

SDL_Point Out_of_Screen(SDL_Point pos){
    SDL_Point pos2;
    pos2.x = pos.x;
    pos2.y = pos.y;
    if (pos.x < 0.0f)	pos2.x = pos.x + 640;
    if (pos.x >= 640)	pos2.x = pos.x - 640;
    if (pos.y < 0.0f)	pos2.y = pos.y + 480;
    if (pos.y >= 480)   pos2.y = pos.y - 480;   
    return pos2; 
}