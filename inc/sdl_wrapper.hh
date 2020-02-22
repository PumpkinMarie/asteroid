#ifndef __SDL_WRAPPER__
#define __SDL_WRAPPER__

#include <SDL.h>
#include <string>

// due to SDL implementation of Robin's laptop.
// cause 2009 bytes definitely lost
// cause 25_509 bytes indirectly lost
// cause 72_571 bytes still reachable
// due to SDL implementation of Marie's laptop.
// cause ?? bytes definitely lost
// cause ?? bytes indirectly lost
// cause ?? bytes still reachable

namespace sdl {
class Sdl {
  public:
    explicit Sdl(); // easy constructor
    virtual ~Sdl(); // destructor

    Sdl(const Sdl& other) = delete;            // not copyable
    Sdl& operator=(const Sdl& other) = delete; // not copyable
    Sdl(Sdl&& other)                 = delete; // not movable
    Sdl& operator=(Sdl&& other) = delete;      // not movable
};

void delay(Uint32 ms);

} // namespace sdl
#endif