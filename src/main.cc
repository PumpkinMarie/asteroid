
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Asteroids.hh"
#include "Bullet.hh"
#include "Ship.hh"
#include "utilitaires.hh"
#include "Game.hh"

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

    srand(time(NULL));

    Game game {window}; 
    bool ship_spawn = false; //savoir si le vaisseau attend l'appui par le joueur pour spawn

    Ship ship {window};
    std::vector<Bullet> Bullets;

    std::vector<Asteroids> asteroids;
    asteroids.push_back(Asteroids {window});
    asteroids.push_back(Asteroids {window});

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

        for (int i = 0; i<asteroids.size();i++){
            if (asteroids[i].isDead()){
                float division = asteroids[i].getRadius()/2;
                SDL_FPoint center = asteroids[i].getCenter();
                if (division > 10){
                    asteroids.push_back(Asteroids {window,division,center});
                    asteroids.push_back(Asteroids {window,division,center});
                }
                asteroids.erase(asteroids.begin()+i);
            }
        }


        for (auto& a : asteroids) {
            a.move();
            a.draw();
            //Work in progress
            if (!ship_spawn && ship.onCollision(a)){
                game.lostLife();
                ship_spawn = true;
                ship.backtothecenter();
                std::cout<<game.getLives()<<std::endl;
                if (game.getLives() == 0)
                    done = SDL_TRUE;        
            }
            if (Bullets.size() > 0) {
            auto i = remove_if(Bullets.begin(), Bullets.end(), [&](Bullet b) {
                return (b.onCollision(a));
            });
            if (i != Bullets.end()){
                Bullets.erase(i);
                a.destruct();
            }
        }
        }

        // Draw Bullets
        for (auto b : Bullets)
            b.render_bullet(renderer);

        if (!ship_spawn)
            ship.draw();

        SDL_RenderPresent(renderer);

        SDL_Delay(8); // 120 fps

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            if (!ship_spawn){
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_LEFT) {
                    ship.rotation(2);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_RIGHT) {
                    ship.rotation(1);
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
                    ship.change_speed(0.1);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_DOWN) {
                    ship.change_speed(0.1);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_SPACE) {
                    Bullets.push_back({ship});
                }
            }
            if (ship_spawn && event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_SPACE) {
                    ship_spawn = false;
            }
        }
        ship.move();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
