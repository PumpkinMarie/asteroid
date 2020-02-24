#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL.h>
#include "renderer_wrapper.hh"
#include <cmath>
#include <stdlib.h>     
#include <time.h>       
#include "utilitaires.hh"


class Asteroids
{
    SDL_Point data_[5];
    float center_[2];
    float angle_; //en degré
    int rayon_;
    float speed_;


    public:   
        Asteroids();
        float getangle() const;
        void drawdata(SDL_Renderer* renderer) const; //dessine les lignes du vaisseau
        void changeData(); //dessine les lignes du vaisseau
        void move(); //déplace le vaisseau selon l'angle angle_direction

};

#endif // ASTEROIDS_H