
#include "renderer_wrapper.hh"
#include "sdl_wrapper.hh"
#include "window_wrapper.hh"

#include <iostream>

using namespace sdl;

int main() {
    try {
	SDL sdl_init(); // automatiquement détruit à la fin du scope
	Window window("Asteroid",
		      SDL_WINDOWPOS_UNDEFINED,
		      SDL_WINDOWPOS_UNDEFINED,
		      640,
		      480,
		      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_bool done = SDL_FALSE;
	while (!done) // display loop
	{
	    SDL_Event event;
	    // à envoyer dans la classe renderer
	    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	    SDL_RenderClear(renderer.get());

	    SDL_SetRenderDrawColor(
	    renderer.get(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	    SDL_RenderDrawLine(renderer.get(), 0, 0, 640, 480);
	    SDL_RenderPresent(renderer.get());
	    // fin à envoyer dans la classe renderer

	    delay(16); // 60 fps
	    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { done = SDL_TRUE; }
	    }
	}

    } catch (std::exception& e) { std::cerr << e.what() << std::endl; }

    return 0;
}
