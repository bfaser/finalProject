#include <iostream>
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../headers/SDL2/window.hpp"
#include "../headers/SDL2/rectangle.hpp"

Rectangle::Rectangle(int w, int h, int position[], SDL_Color color):
    _w(w), _h(h)
{
    _x = position[0];
    _y = position[1];

    _color = color;
    secondaryColor.r = color.r / 2;
    secondaryColor.g = color.g / 2;
    secondaryColor.b = color.b / 2;
    secondaryColor.a = color.a;
    isButton = false;
    event = nullptr;

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

    _color = {0,0,0,0};

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

void Rectangle::draw(SDL_Event &event) {
    if (_texture) {
        SDL_RenderCopy(Window::renderer, _texture, nullptr, &_rectangle);
    }
    else {
        SDL_SetRenderDrawColor(Window::renderer, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderFillRect(Window::renderer, &_rectangle);
    }
}

void Rectangle::define(int w, int h, int positionX, int positionY, SDL_Color color) {
    _w = w;
    _h = h;

    _x = positionX;
    _y = positionY;

    _color = color;

    _rectangle.w = _w;
    _rectangle.h = _h;
    _rectangle.x = _x - (_w / 2);
    _rectangle.y = _y - (_h / 2);
}

SDL_Color Rectangle::getColor() const {
    return _color;
}

SDL_Rect Rectangle::getRectObject() const {
    return _rectangle;
}

void Rectangle::setColor(SDL_Color color) {
    _color = color;
}

void Rectangle::setPosition (int position[]) {
    _x = position[0];
    _y = position[1];
}

void Rectangle::setDimensions (int w, int h) {
    _w = w; 
    _h = h;
}

void Rectangle::setButton(bool isButton, SDL_Event &event) {
    this->isButton = isButton;
    this->event  = &event;
}

bool Rectangle::getButtonState () const {
    return isButton;
}


bool Rectangle::isClicked(SDL_Event &event) {
    bool hovered = mouseOver(event);
    bool clicked = (event.type == SDL_MOUSEBUTTONDOWN);
    return (hovered && clicked);
}

bool Rectangle::mouseOver(SDL_Event &event) {
    int leftSide, rightSide, topSide, bottomSide;
    leftSide = _x - (_w / 2);
    rightSide = _x + (_w / 2);
    topSide = _y - (_h / 2);
    bottomSide = _y + (_h / 2);

    int mX, mY;

    mX = event.motion.x;
    mY = event.motion.y;

    bool inside = (leftSide < mX && mX < rightSide && topSide < mY && mY < bottomSide);
    return inside;
}