#ifndef SHIP_H
#define SHIP_H

#include <SDL.h>
#include "renderer_wrapper.hh"
#include <cmath>


class Ship
{
    SDL_Point data_[5];
    float center_[2];
    float angle_; //en degré
    float angle_move_; //angle de direction du vaisseau
    float angle_tmp_; //angle de direction du vaisseau
    float speed_;


    public:   
        Ship();
        SDL_Point getdatafirst() const;
        float getangle() const;
        void drawdata(SDL_Renderer* renderer) const; //dessine les lignes du vaisseau
        void move(); //déplace le vaisseau selon l'angle angle_direction
        void rotation(int direction); 
        void rotation_data(float angle);
        void rotation_render();
        void change_speed(int vitesse);

};

#endif // SHIP_H