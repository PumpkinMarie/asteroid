#include <SDL.h>

#include <cmath>
#include <iostream>

SDL_Point Out_of_Screen(SDL_Point pos);
void SDL_RenderDrawCircleF(
    SDL_Renderer*, SDL_FPoint, float); // using Midpoint Circle Algorithm