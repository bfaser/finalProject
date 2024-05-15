/***************************************
*   This File has been adapted from the YouTube tutorial series on SDL2
*
****************************************/
#include <iostream>
#include <string>
#include "../headers/SDL2/text.hpp"
#include "../headers/SDL2/window.hpp"
#include "../headers/SDL2/rectangle.hpp"

Text::Text() {}

Text::~Text() {
    if (_text_texture != nullptr) {
        SDL_DestroyTexture(_text_texture);
    }
}

Text::Text(SDL_Renderer *renderer, int font_size, const std::string &message, const SDL_Color &color, int characterLimit, const std::string &font_path){
    this->characterLimit = characterLimit;
    std::string newMessage = message.substr(0, characterLimit);
    _text_texture = loadFont(renderer, font_path, font_size, newMessage, color);
    SDL_QueryTexture(_text_texture, nullptr, nullptr, &_textRectangle.w, &_textRectangle.h);
}

void Text::display(int x, int y, SDL_Renderer *renderer) const {
    if (!_linked) {
        _textRectangle.x = x - (_textRectangle.w / 2);
        _textRectangle.y = y - (_textRectangle.h / 2);
    }

    SDL_RenderCopy(renderer, _text_texture, nullptr, &_textRectangle);
}

void Text::display() const {
    if (!_linked) {return;}
    SDL_RenderCopy(Window::renderer, _text_texture, nullptr, &_textRectangle);
}

void Text::linkRect(Rectangle targetRectangle) {
    SDL_Rect textRectangle = targetRectangle.getRectObject();
    int x, y;
    x = textRectangle.x + textRectangle.w / 2;
    y = textRectangle.y + textRectangle.h / 2;
    textRectangle.w /= 1.5;
    textRectangle.h /= 1.5;
    textRectangle.x = x - textRectangle.w / 2;
    textRectangle.y = y - textRectangle.h / 2;
    _textRectangle = textRectangle;
    _linked = true;
}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) {
        std::cerr << "Failed to load font\n";
    }

    SDL_Surface *text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!text_surface) {
        std::cerr << "Failed to create text surface\n";
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        std::cerr << "Failed to create text texture\n";
    }
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return text_texture;
}

void Text::defineObj(SDL_Renderer *renderer, int font_size, const std::string &message, const SDL_Color &color, int characterLimit, const std::string &font_path) {
    this->characterLimit = characterLimit;
    std::string newMessage;
    if (characterLimit > 0) {
        newMessage = message.substr(0, characterLimit);
    } else {
        newMessage = message;
    }
    _text_texture = loadFont(renderer, font_path, font_size, newMessage, color);
    SDL_QueryTexture(_text_texture, nullptr, nullptr, &_textRectangle.w, &_textRectangle.h);
}