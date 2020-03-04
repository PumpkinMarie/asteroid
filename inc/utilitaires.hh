#include <SDL.h>

#include <cmath>
#include <iostream>

SDL_Point Out_of_Screen(SDL_Point pos);
void SDL_RenderDrawCircleF(
    SDL_Window*, SDL_FPoint, float); // using Midpoint Circle Algorithm
float wrap(float x, int limit);

bool PointdansCercle(float px, float py,SDL_FPoint center, float radius);