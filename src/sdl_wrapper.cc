#include "sdl_wrapper.hh"

namespace sdl {
Sdl::Sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
	throw "SDL_init failed: " + std::string(SDL_GetError());
    }
}

Sdl::~Sdl() { SDL_Quit(); }

void delay(Uint32 ms) { SDL_Delay(ms); }
} // namespace sdl