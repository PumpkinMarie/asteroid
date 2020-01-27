#include "renderer_wrapper.hh"

Renderer::Renderer(Window& win, int index, Uint32 flags) {
    if ((renderer = SDL_CreateRenderer(win.get(), index, flags)) == nullptr) {
	throw "SDL_CreateRenderer failed: " + std::string(SDL_GetError());
    }
}

Renderer::~Renderer() {
    if (renderer != nullptr) {
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
    }
}

SDL_Renderer* Renderer::get() const { return renderer; }
