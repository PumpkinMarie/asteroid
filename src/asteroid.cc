
#include "renderer_wrapper.hh"
#include "sdl_wrapper.hh"
#include "window_wrapper.hh"
#include "Ship.hh"
#include "Bullet.hh"
#include "Asteroids.hh"
#include "utilitaires.hh"

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

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

	Ship ship;
	std::vector<Bullet> Bullets;

	std::vector<Asteroids> Asteroids;
	Asteroids.push_back({});
	Asteroids.push_back({});

	while (!done) // display loop
	{
	    SDL_Event event;

	    renderer.setDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
	    renderer.clear();

	    renderer.setDrawColor(255, 255, 255, SDL_ALPHA_OPAQUE);

	    //renderer.drawLine(
	    //0, 0, window.getScreenSize().first, window.getScreenSize().second);


		// Update Bullets
		for (auto &b : Bullets)
			b.move_bullet();

		if (Bullets.size() > 0)
		{
			auto i = remove_if(Bullets.begin(), Bullets.end(), [&](Bullet b) { return (b.getTime()<=0); });
			if (i != Bullets.end())
				Bullets.erase(i);
		}

		for (auto &a : Asteroids)
			a.move();

		// Draw Bullets
		for (auto b : Bullets)
			b.render_bullet(renderer.get());

		for (auto a : Asteroids)
			a.drawdata(renderer.get());

		SDL_RenderPresent(renderer.get());
		ship.drawdata(renderer.get());

	    renderer.present();
	    // fin à envoyer dans la classe renderer

			    delay(16); // 60 fps
			    
	    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) { done = SDL_TRUE; }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) { ship.rotation(1); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) { ship.rotation(2); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) { ship.change_speed(1); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) { ship.change_speed(-1); }
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) 
		{
			Bullets.push_back({ ship });	}
	    }
		ship.move();
	}

	// ordering of destroyer
	renderer.~Renderer();
	window.~Window();
	sdl.~Sdl();
    } catch (std::exception& e) { std::cerr << e.what() << std::endl; }

    return 0;
}
