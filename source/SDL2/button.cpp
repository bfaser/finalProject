#include <SDL2/rectangle.hpp>
#include <SDL2/button.hpp>

Button::Button () {
    
}

Button::Button (Rectangle button) {
    buttonRectangle = button;
}

Button::~Button() {
    
}

bool Button::isClicked(SDL_Event &event) {
    bool hovered = mouseOver(event);
    bool clicked = (event.type == SDL_MOUSEBUTTONDOWN);
    return (hovered && clicked);
}

bool Button::mouseOver(SDL_Event &event) {
    SDL_Rect rect = buttonRectangle.getRectObject();

    int left, right, top, bottom;
    left = rect.x - (rect.w / 2);
    right = rect.x + (rect.w / 2);
    top = rect.y - (rect.h / 2);
    bottom = rect.y + (rect.h / 2);

    int mX, mY;
    mX = event.motion.x;
    mY = event.motion.y;

    bool inside = (left < mX && mX < right && bottom < mY && mY < top);
    return inside;
}