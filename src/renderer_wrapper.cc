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

int Renderer::setDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    return SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

int Renderer::clear() { return SDL_RenderClear(renderer); }

int Renderer::drawLine(int x1, int y1, int x2, int y2) {
    return SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

int Renderer::present() { SDL_RenderPresent(renderer); }
