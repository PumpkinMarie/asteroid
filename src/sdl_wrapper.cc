#include "sdl_wrapper.hh"

SDL::SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	throw "SDL_init failed: " + std::string(SDL_GetError());
    }
}

SDL::~SDL() { SDL_Quit(); }