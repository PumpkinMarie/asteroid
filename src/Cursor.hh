#ifndef CURSOR_H
#define CURSOR_H

#include <SDL.h>
#include "renderer_wrapper.hh"
#include <cmath>


class Cursor
{
    SDL_Point data_[5];
    SDL_Point centre_;
    float angle_;

    public:   
        Cursor();
        SDL_Point getdata() const;
        void drawdata(SDL_Renderer* renderer) const;
        void move(int direction) ;
        void rotation(int direction) ;
        void rotation_data(float angle) ;
        void fct_du_soir() ;

};

#endif // CURSOR_H