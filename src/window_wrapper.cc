#include "window_wrapper.hh"

#include <iostream>

Window::Window(
const std::string& title, int x, int y, int w, int h, Uint32 flags) {
    if ((window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) ==
	nullptr) {
	throw "SDL_CreateWindow failed: " + std::string(SDL_GetError());
    }
}

Window::~Window() {
    if (window != nullptr) {
	SDL_DestroyWindow(window);
	window = nullptr;
    }
}

SDL_Window* Window::get() const { return window; }

std::pair<int, int> Window::getScreenSize() const {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return std::pair<int, int>(w, h);
}