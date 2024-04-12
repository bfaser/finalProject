#include <iostream>
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../headers/SDL2/window.hpp"
#include "../headers/SDL2/rectangle.hpp"

Rectangle::Rectangle(int w, int h, int position[], SDL_Color color):
    _w(w), _h(h)
{
    _x = position[0];
    _y = position[1];

    _r = color.r;
    _g = color.g;
    _b = color.b;
    _a=  color.a;

    _rectangle.w = _w;
    _rectangle.h = _h;
    _rectangle.x = _x - (_w / 2);
    _rectangle.y = _y - (_h / 2);
}

Rectangle::Rectangle() {
    _w = 0;
    _h = 0;

    _x = 0;
    _y = 0;

    _r = 0;
    _g = 0;
    _b = 0;
    _a =  0;

    _rectangle.w = _w;
    _rectangle.h = _h;
    _rectangle.x = _x - (_w / 2);
    _rectangle.y = _y - (_h / 2);
}

Rectangle::Rectangle(int w, int h, int position[], const std::string &image_path):
    _w(w), _h(h)
{
    _x = position[0];
    _y = position[1];

    SDL_Surface *surface = IMG_Load(image_path.c_str());
    if (!surface) {
        std::cerr << "Failed to create surface\n";
    }

    _texture = SDL_CreateTextureFromSurface(Window::renderer, surface);

    if (!_texture) {
        std::cerr << "Failed to create texture\n";
    }
    
    _rectangle.w = _w;
    _rectangle.h = _h;
    _rectangle.x = _x - (_w / 2);
    _rectangle.y = _y - (_h / 2);

    SDL_FreeSurface(surface);
}

Rectangle::~Rectangle() {
    SDL_DestroyTexture(_texture);
}

void Rectangle::draw() {
    if (_texture) {
        SDL_RenderCopy(Window::renderer, _texture, nullptr, &_rectangle);
    }
    else {
        SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
        SDL_RenderFillRect(Window::renderer, &_rectangle);
    }
}

void Rectangle::define(int w, int h, int positionX, int positionY, SDL_Color color) {
    _w = w;
    _h = h;

    _x = positionX;
    _y = positionY;

    _r = color.r;
    _g = color.g;
    _b = color.b;
    _a=  color.a;

    _rectangle.w = _w;
    _rectangle.h = _h;
    _rectangle.x = _x - (_w / 2);
    _rectangle.y = _y - (_h / 2);
}

SDL_Rect Rectangle::rectObject() const {
    return _rectangle;
}