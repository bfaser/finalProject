#ifndef BUTTON_HPP
#define BUTTON_HPP

#include<SDL2/rectangle.hpp>
#include<SDL2/window.hpp>

class Button {
    private:
        Rectangle buttonRectangle;
        bool mouseOver(SDL_Event &event);
    public:
        Button();
        Button(Rectangle button);
        ~Button();

        bool isClicked(SDL_Event &event);
};

#endif