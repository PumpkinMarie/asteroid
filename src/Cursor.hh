#ifndef CURSOR_H
#define CURSOR_H

#include <SDL.h>
#include "renderer_wrapper.hh"


class Cursor
{
    SDL_Point data_[5];
    SDL_Point destination;

    public:   
        Cursor();
        SDL_Point getdata() const;
        void drawdata(SDL_Renderer* renderer) const;
        void move(int direction) ;
        void rotation(int direction) ;

};

#endif // CURSOR_H