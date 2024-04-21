#include <iostream>
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../headers/SDL2/window.hpp"


SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string &title, int width, int height):
_title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL.\n";
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG /*| IMG_INIT_JPG*/ ) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL Image.\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL TTF.\n";
        return false;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

    if (_window == nullptr) {
        std::cerr << "Failed to create window.\n";
        return false;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

     if (renderer == nullptr) {
        std::cerr << "Failed to create renderer.\n";
        return false;
    }

    return true;
}

bool Window::isClosed() const {
    return _closed;
}

int Window::getWidth() const {
    return _width;
}


int Window::getHeight() const {
    return _height;
}

void Window::clear(SDL_Color color) {
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Window::close() {
    _closed = true;
}

void Window::pollEvents(SDL_Event &event) {
        switch (event.type) {
            case SDL_QUIT:
                _closed = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    _closed = true;
                    break;
                default:
                    break;
                }
            case SDL_MOUSEMOTION:
                // std::cout << "(" << event.motion.x << "," << event.motion.y <<")\n";
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            default:
                break;
        }
}