#ifndef CURSOR_H
#define CURSOR_H

#include <SDL.h>
#include "renderer_wrapper.hh"


class Cursor
{
    SDL_Point data_[5];

    public:   
        Cursor();
        SDL_Point getdata() const;
        void drawdata(SDL_Renderer* renderer) const;

};

#endif // CURSOR_H