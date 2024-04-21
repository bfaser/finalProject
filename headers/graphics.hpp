#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define SDL_MAIN_HANDLED
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"
#include "..\headers\games\wordle.hpp"


// Rendering Functions (reusable)

std::string checkStringLength (std::string inputString, int charLength);

char lower (char* input);
/*  (void) gridCreate Function
    gridCreate function produces a display of (rows) x (columns) rectangles
    rows = placement[0]
    columns = placement[1]
    For multiBuffer boolean value as false, 
        placement[2] will be the top, bottom and side buffer, where the grid will not be drawn onto
        there is no separation of grid cells (no buffer between cells)
    When multibuffer is true,
        placement[2] will be the top buffer width in pixels
        placement[3] will be the bottom buffer width in pixels
        placement[4] will be the side buffer width in pixels
        placement[5] will be the cell-to-cell buffer width in pixels
    rectangleText is an array of strings in the test class that are to be rendered at the center of the each grid cell
    Since an array of rectangle objects is passed in, the objects themselves are modified, hence the void return of the function
*/  

void gridCreate(Window &window, int placement[], SDL_Color color[], Rectangle rectangleArray[], bool multiBuffer = false, Text rectangleText[] = nullptr);

void writeTexts (Text textArray[], std::string stringArray[], int dimensions[], SDL_Color color = {0,0,0,255}, int charLimit = 1);

// Games and Windows
int showGraphics (); // Possibly convert to the sign-in page
void pollEvent (Window &window, Rectangle buttonArray[]);
int showWordle (Wordle &wordleInstance);
void pollWordleEvents (Window &window, std::string inputString[], int& trial, Wordle &wordleInstance);
bool wordleSubmit (Wordle &wordleInstance, std::string enteredWord, int trial);

// Sign-in window function
// Connections window function
// Hangman window function

template <typename Type> 
int binarySearch (Type key, std::vector<Type> array);
template <typename Type>
int binarySearch (std::vector<Type> array, Type key, int low, int high);

#endif