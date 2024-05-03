#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>
#include "window.hpp"

class Rectangle {
    private:
        int _w;
        int _h;
        int _x, _y; // Position[2] = {_x, _y}
        bool isButton;
        SDL_Color _color;
        SDL_Color secondaryColor;
        SDL_Rect _rectangle;
        SDL_Texture *_texture = nullptr;
        SDL_Event *event;
        
    public:
        bool mouseOver(SDL_Event &event);
        Rectangle();
        Rectangle(int w, int h, int position[], SDL_Color color); // Colored Rectangle
        Rectangle(int w, int h, int position[], const std::string &image_path); // Image 
        ~Rectangle();

        void draw(SDL_Event &event); // Add the rectangle to the renderer queue
        void define(int w, int h, int positionX, int positionY, SDL_Color color); // define / redefine the Rectangle object

        // Setters
        void setColor (SDL_Color color);
        void setPosition (int position[]);
        void setDimensions (int w, int h);
        void setButton (bool isButton, SDL_Event &event);

        // Getters
        SDL_Color getColor () const;
        SDL_Rect getRectObject() const; // Returns the rectangle object (used to link text in Text class)
        bool getButtonState () const;


        // Button Implementation        
        bool isClicked(SDL_Event &event);
};

#endif