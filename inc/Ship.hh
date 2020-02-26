#ifndef SHIP_H
#define SHIP_H

#include <SDL.h>

#include <cmath>

class Ship {
    SDL_Window* const window_;
    SDL_FPoint center_;
    SDL_FPoint speed_;
    float angle_; // en degré

   public:
    Ship(SDL_Window*);
    SDL_Point getdatafirst() const;
    float getangle() const;
    void draw() const; // dessine les lignes du vaisseau
    void move();       // déplace le vaisseau selon l'angle angle_direction
    void rotation(int direction);
    // void rotation_data(float angle);
    // void rotation_render();
    void change_speed(float vitesse);
};

#endif // SHIP_H