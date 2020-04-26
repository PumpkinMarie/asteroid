
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Asteroids.hh"
#include "Bullet.hh"
#include "Game.hh"
#include "Ship.hh"
#include "SpaceObject.hh"
#include "random.hh"
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
    if (SDL_CreateWindowAndRenderer(1900,
            1080,
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

    Game game{window};
    bool ship_spawn =
        false; // savoir si le vaisseau attend l'appui par le joueur pour spawn
    bool start_game     = true;
    bool end_game       = false;
    bool end_game_score = false;
    Ship ship           = Ship(window);
    std::vector<Bullet> Bullets;

    std::vector<Asteroids> asteroids;
    for (int i = 0; i < getRandom(15, 20); i++) {
        asteroids.push_back(Asteroids{window, ship.getCenter()});
    }
    while (!done) // display loop
    {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);

        game.drawLives();
        game.drawScore();
        if (start_game)
            game.drawStartMenu();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // Update Bullets

        if (!start_game && !end_game) {
            for (auto& b : Bullets)
                b.moveBullet();

            if (Bullets.size() > 0) {
                auto i = remove_if(Bullets.begin(),
                    Bullets.end(),
                    [&](Bullet b) { return (b.getTime() <= 0); });
                if (i != Bullets.end())
                    Bullets.erase(i);
            }

            for (int i = 0; i < asteroids.size(); i++) {
                if (asteroids[i].isDead()) {
                    float division    = asteroids[i].getRadius() / 2;
                    SDL_FPoint center = asteroids[i].getCenter();
                    if (division > 10) {
                        asteroids.push_back(
                            Asteroids{window, division, center});
                        asteroids.push_back(
                            Asteroids{window, division, center});
                    }
                    asteroids.erase(asteroids.begin() + i);
                }
            }
            for (auto& a : asteroids) {
                a.move();
                a.wrapCoordinates();
                a.draw();
                // Work in progress
                if (!ship_spawn && ship.onCollision(a)) {
                    game.lostLife();
                    ship_spawn = true;
                    ship.placeCenter();
                    if (game.getLives() == 0)
                        end_game = true;
                }
                if (Bullets.size() > 0) {
                    auto i = remove_if(Bullets.begin(),
                        Bullets.end(),
                        [&](Bullet b) { return (b.onCollision(a)); });
                    if (i != Bullets.end()) {
                        Bullets.erase(i);
                        a.destruct();
                        game.score(Asteroids::RADIUS_MAX / a.getRadius() * 10);
                    }
                }
            }
            // Draw Bullets
            for (auto b : Bullets)
                b.draw();

            if (!ship_spawn)
                ship.draw();
        }

        if (end_game) {
            if (end_game_score) {
                game.saveScore();
                game.drawScores();
                end_game_score = false;
            } else
                game.drawEndMenu();
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(8); // 120 fps

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            if (start_game && event.key.keysym.sym == SDLK_RETURN) {
                start_game = false;
            }
            if (!ship_spawn) {
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_LEFT) {
                    ship.rotation(2);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_RIGHT) {
                    ship.rotation(1);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_UP) {
                    ship.changeSpeed(0.1);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_DOWN) {
                    ship.changeSpeed(0.1);
                }
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_SPACE) {
                    Bullets.push_back(Bullet{ship});
                }
            }
            if (!start_game && ship_spawn && event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_SPACE) {
                ship_spawn = false;
            }

            if (end_game_score && event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_RETURN) {
                done = SDL_TRUE;
            }

            if (end_game && event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    game.changeNameIndexMinus();
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    game.changeNameIndexPlus();
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    game.changeCaraPlus();
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    game.changeCaraMinus();
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    end_game_score = true;
                }
            }
        }
        ship.move();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
