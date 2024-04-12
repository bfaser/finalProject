#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>
#include "..\SDL2\include\SDL2\SDL_ttf.h"
#include "..\SDL2\include\SDL2\SDL.h"
#include "../headers/SDL2/rectangle.hpp"

class Text {
private:
    SDL_Texture *_text_texture = nullptr;
    bool _linked = false;
    int characterLimit = 0;
    mutable SDL_Rect _textRectangle;
public:
    Text();
    Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color);
    Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color, int characterLimit);
    
    static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color);
    void display(int x, int y, SDL_Renderer *renderer) const;
    void display() const;

    void linkRect(Rectangle targetRectangle);
    void defineObj(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color, int characterLimit);
};

#endif