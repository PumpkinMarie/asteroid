#include "Game.hh"

Game::Game(SDL_Window* w)
    : window_(w) {}

int Game::getLives() const{return lives_;}

void Game::lostLife(){
    lives_--;
}

void draw(int width, int height, SDL_Window* window)
     {
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    float mx[3]            = {0.0f, -2.5f, +2.5f};
    float my[3]            = {-5.5f, +2.5f, +2.5f};
    float sx[3];
    float sy[3];

    // rotate
    for (int i = 0; i < 3; i++) {
        sx[i] = mx[i] * cosf(0) - my[i] * sinf(0);
        sy[i] = mx[i] * sinf(0) + my[i] * cosf(0);
    }
    // scale
    for (int i = 0; i < 3; i++) {
        sx[i] = sx[i] * 3;
        sy[i] = sy[i] * 3;
    }
    // translate
    for (int i = 0; i < 3; i++) {
        sx[i] += width;
        sy[i] += height;
    }
    // draw
    for (int i = 0; i < 4; i++) {
        int j = i + 1;
        SDL_RenderDrawLineF(
            renderer, sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3]);
    }
}

void Game::drawLives() const{
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
    
    for (int i =1; i <= lives_;i++){
        draw(20*i,20,window_);
    }

}
