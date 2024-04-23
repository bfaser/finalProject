#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "../SDL2/include/SDL2/SDL.h"

class Window {
private:
    std::string _title;
    int _width = 480;
    int _height = 640;
    bool _closed = false;
    SDL_Window *_window = nullptr;

    bool init();
    
public:
    static SDL_Renderer *renderer;

    Window(const std::string &title, int width, int height);
    ~Window();

    void  close ();
    bool isClosed() const;
    void pollEvents(SDL_Event &event);
    void clear(SDL_Color color);
    int getWidth() const;
    int getHeight() const;
    SDL_Window* window();
};

#endif