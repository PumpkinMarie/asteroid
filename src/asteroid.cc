
#include "renderer_wrapper.hh"
#include "sdl_wrapper.hh"
#include "window_wrapper.hh"
#include "Cursor.hh"

#include <iostream>
#include <utility>

using namespace sdl;


int main() {
    try {
	Sdl sdl; // automatiquement détruit à la fin du scope
	Window window("Asteroid",
		      SDL_WINDOWPOS_UNDEFINED,
		      SDL_WINDOWPOS_UNDEFINED,
		      640,
		      480,
		      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_bool done = SDL_FALSE;

	Cursor c;
	while (!done) // display loop
	{
	    SDL_Event event;

	    renderer.setDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
	    renderer.clear();

	    renderer.setDrawColor(255, 255, 255, SDL_ALPHA_OPAQUE);

	    //renderer.drawLine(
	    //0, 0, window.getScreenSize().first, window.getScreenSize().second);

		SDL_RenderPresent(renderer.get());
		c.drawdata(renderer.get());

	    renderer.present();
	    // fin à envoyer dans la classe renderer
	    
			    delay(16); // 60 fps
			    
	    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { done = SDL_TRUE; }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) { c.rotation(1); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) { c.rotation(2); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) { c.move(1); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) { c.move(2); }
	    }
	}

	// ordering of destroyer
	renderer.~Renderer();
	window.~Window();
	sdl.~Sdl();
    } catch (std::exception& e) { std::cerr << e.what() << std::endl; }

    return 0;
}
