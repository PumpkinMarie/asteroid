#include "Game.hh"

Game::Game(SDL_Window* w)
    : window_(w) {}

int Game::getLives() const{return lives_;}

void Game::lostLife(){
    lives_--;
}


void Game::drawLives() const{
    int width;
    int height;
    SDL_GetWindowSize(window_, &width, &height);
}
