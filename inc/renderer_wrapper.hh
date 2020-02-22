#ifndef __RENDERER_WRAPPER__
#define __RENDERER_WRAPPER__

#include "window_wrapper.hh"

#include <SDL.h>
#include <string>

class Renderer {
    SDL_Renderer* renderer; // Renderer to manipulate;
  public:
    explicit Renderer(Window&, int, Uint32);
    virtual ~Renderer();
    SDL_Renderer* get() const;
    int setDrawColor(Uint8, Uint8, Uint8, Uint8);
    int clear();
    int drawLine(int, int, int, int);
    int present();

    Renderer(const Renderer&) = delete;            // not copyable
    Renderer& operator=(const Renderer&) = delete; // not copyable
    Renderer(Renderer&&)                 = delete; // not movable
    Renderer& operator=(Renderer&&) = delete;      // not movable
};

#endif