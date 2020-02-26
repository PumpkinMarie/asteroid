#include "utilitaires.hh"

#include <SDL.h>

void SDL_RenderDrawCircleF(SDL_Renderer* r,
    SDL_FPoint center,
    float radius) { // Midpoint Circle Algorithm
    const auto diameter = radius * 2.;
    float x             = (radius - 1.);
    float y             = 0;
    float tx            = 1;
    float ty            = 1;
    float error         = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawPointF(r, center.x + x, center.y - y);
        SDL_RenderDrawPointF(r, center.x + x, center.y + y);
        SDL_RenderDrawPointF(r, center.x - x, center.y - y);
        SDL_RenderDrawPointF(r, center.x - x, center.y + y);
        SDL_RenderDrawPointF(r, center.x + y, center.y - x);
        SDL_RenderDrawPointF(r, center.x + y, center.y + x);
        SDL_RenderDrawPointF(r, center.x - y, center.y - x);
        SDL_RenderDrawPointF(r, center.x - y, center.y + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

SDL_Point Out_of_Screen(SDL_Point pos) {
    SDL_Point pos2;
    pos2.x = pos.x;
    pos2.y = pos.y;
    if (pos.x < 0)
        pos2.x = pos.x + 640;
    if (pos.x >= 640)
        pos2.x = pos.x - 640;
    if (pos.y < 0)
        pos2.y = pos.y + 480;
    if (pos.y >= 480)
        pos2.y = pos.y - 480;
    return pos2;
}