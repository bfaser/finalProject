#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define SDL_MAIN_HANDLED
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"

void pollEvents(Window &window);
void gridOfRects(Window &window, int placement[], SDL_Color color, Rectangle rectangleArray[], bool multiBuffer, Text rectangleText[]);

int showGraphics ();
int showWordle (std::string fiveLetter[]);

#endif