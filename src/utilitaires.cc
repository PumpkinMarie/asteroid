#include "utilitaires.hh"

#include <SDL.h>

void SDL_RenderDrawCircleF(SDL_Window* w,
    SDL_FPoint center,
    float radius) { // Midpoint Circle Algorithm
    SDL_Renderer* r     = SDL_GetRenderer(w);
    const auto diameter = radius * 2.;
    float x             = (radius - 1.);
    float y             = 0;
    float tx            = 1;
    float ty            = 1;
    float error         = (tx - diameter);
    int height, width;
    SDL_GetWindowSize(w, &width, &height);
    while (x >= y) {
        SDL_RenderDrawPointF(
            r, wrap(center.x + x, width), wrap(center.y - y, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x + x, width), wrap(center.y + y, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x - x, width), wrap(center.y - y, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x - x, width), wrap(center.y + y, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x + y, width), wrap(center.y - x, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x + y, width), wrap(center.y + x, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x - y, width), wrap(center.y - x, height));
        SDL_RenderDrawPointF(
            r, wrap(center.x - y, width), wrap(center.y + x, height));

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

float wrap(float f, int limit) {
    if (f < 0)
        return f + limit;
    else if (f >= (float)limit)
        return f - limit;
    else
        return f;
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

bool PointdansCercle(float px, float py,SDL_FPoint center, float radius){
    return sqrt((px-center.x)*(px-center.x) + (py-center.y)*(py-center.y)) < radius;
}