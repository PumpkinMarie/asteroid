#ifndef __RENDERER_WRAPPER__
#define __RENDERER_WRAPPER__

#include "window_wrapper.hh"

#include <SDL.h>
#include <string>

class Renderer {
    SDL_Renderer* renderer; // Renderer to manipulate;
  public:
    explicit Renderer(Window& window, int index, Uint32 flags);
    virtual ~Renderer();
    SDL_Renderer* get() const;
    std::pair<int, int> getScreenSize() const;
    int getWidth() const;
    int getHeight() const;
    std::string getTitle() const;
    Renderer& Maximize();
    Renderer& Minimize();
    Renderer& Restore();
    Renderer& hide();
    Renderer& show();

    Renderer(const Renderer& other) = delete;            // not copyable
    Renderer& operator=(const Renderer& other) = delete; // not copyable
    Renderer(Renderer&& other)                 = delete; // not movable
    Renderer& operator=(Renderer&& other) = delete;      // not movable
};

#endif