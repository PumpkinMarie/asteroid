#include "sdl_wrapper.hh"

namespace sdl {
SDL::SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	throw "SDL_init failed: " + std::string(SDL_GetError());
    }
}

SDL::~SDL() { SDL_Quit(); }

void delay(Uint32 ms) { SDL_Delay(ms); }
} // namespace sdl