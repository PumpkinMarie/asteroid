#ifndef __WINDOW_WRAPPER__
#define __WINDOW_WRAPPER__

#include <SDL.h>
#include <string>

class Window {
    SDL_Window* window; // window to manipulate;
  public:
    explicit Window(
    const std::string& title, int x, int y, int w, int h, Uint32 flags);
    virtual ~Window();
    SDL_Window* get() const;
    std::pair<int, int> getScreenSize() const;
    int getWidth() const;
    int getHeight() const;
    std::string getTitle() const;
    Window& Maximize();
    Window& Minimize();
    Window& Restore();
    Window& hide();
    Window& show();

    Window(const Window& other) = delete;            // not copyable
    Window& operator=(const Window& other) = delete; // not copyable
    Window(Window&& other)                 = delete; // not movable
    Window& operator=(Window&& other) = delete;      // not movable
};

#endif