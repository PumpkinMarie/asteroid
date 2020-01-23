
#include "sdl_wrapper.hh"
#include "window_wrapper.hh"

#include <iostream>

int main() {
    try {
	SDL sdl(); // automatiquement détruit à la fin du scope
	Window window("Asteroid",
		      SDL_WINDOWPOS_UNDEFINED,
		      SDL_WINDOWPOS_UNDEFINED,
		      640,
		      480,
		      SDL_WINDOW_SHOWN);

	if (window.get() != nullptr) {
	    SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie
				la fenêtre */
	}
    } catch (std::exception& e) { std::cerr << e.what() << std::endl; }

    return 0;
}
