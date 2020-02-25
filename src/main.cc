
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Asteroids.hh"
#include "Bullet.hh"
#include "Ship.hh"
#include "utilitaires.hh"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't initialize SDL: %s",
            SDL_GetError());
        return 3;
    }
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (SDL_CreateWindowAndRenderer(640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            &window,
            &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Couldn't create window and renderer: %s",
            SDL_GetError());
        return 3;
    }
    SDL_bool done = SDL_FALSE;

    Ship ship;
    std::vector<Bullet> Bullets;

    std::vector<Asteroids> Asteroids;
    Asteroids.push_back({});
    Asteroids.push_back({});

    while (!done) // display loop
    {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // Update Bullets
        for (auto& b : Bullets)
            b.move_bullet();

        if (Bullets.size() > 0) {
            auto i = remove_if(Bullets.begin(), Bullets.end(), [&](Bullet b) {
                return (b.getTime() <= 0);
            });
            if (i != Bullets.end())
                Bullets.erase(i);
        }

        for (auto& a : Asteroids)
            a.move();

        // Draw Bullets
        for (auto b : Bullets)
            b.render_bullet(renderer);

        for (auto a : Asteroids)
            a.drawdata(renderer);

        SDL_RenderPresent(renderer);

        ship.drawdata(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(8); // 120 fps

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_LEFT) {
                ship.rotation(1);
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_RIGHT) {
                ship.rotation(2);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
                ship.change_speed(1);
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_DOWN) {
                ship.change_speed(-1);
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_SPACE) {
                Bullets.push_back({ship});
            }
        }
        ship.move();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
