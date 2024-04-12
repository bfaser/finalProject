#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>
#include "window.hpp"

class Rectangle {
    private:
        int _w;
        int _h;
        int _x, _y; // Position[2] = {_x, _y}
        int _r, _g, _b, _a; // Color[4] = {_r, _g, _b, _a}
        SDL_Rect _rectangle;
        SDL_Texture *_texture = nullptr;
    public:
        Rectangle();
        Rectangle(int w, int h, int position[], SDL_Color color);
        Rectangle(int w, int h, int position[], const std::string &image_path);
        ~Rectangle();

        void draw();
        void define(int w, int h, int positionX, int positionY, SDL_Color color);
        SDL_Rect rectObject() const;
};

#endif