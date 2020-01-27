#ifndef __SDL_WINDOW_WRAPPER__
#define __SDL_WINDOW_WRAPPER__

#include <SDL2/SDL.h>
#include <string>

namespace sdl {
class SDL {
  public:
    explicit SDL(); // easy constructor
    virtual ~SDL(); // destructor

    SDL(const SDL& other) = delete;            // not copyable
    SDL& operator=(const SDL& other) = delete; // not copyable
    SDL(SDL&& other)                 = delete; // not movable
    SDL& operator=(SDL&& other) = delete;      // not movable
};

void delay(Uint32 ms);

} // namespace sdl
#endif