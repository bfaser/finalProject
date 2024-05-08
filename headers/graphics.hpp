#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#define SDL_MAIN_HANDLED
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"
#include "..\headers\games\wordle.hpp"

// Rendering Functions (reusable)

std::string checkStringLength (std::string inputString, int charLength);

char lower (char input);
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

void gridCreate(Window &window, int placement[], std::vector<SDL_Color> &color, Rectangle rectangleArray[], bool multiBuffer = false, Text rectangleText[] = nullptr);

void writeTexts (Text textArray[], std::vector<std::string> &stringArray, int dimensions[], SDL_Color color = {0,0,0,255}, int charLimit = 1);

// Games and Windows
int mainMenu (); // Possibly convert to the sign-in page
void pollEventMenu (Window &window, Rectangle buttonArray[], SDL_Event &event);
void displayMenu (Rectangle buttonsArray[], Text buttonTexts[], int size, SDL_Event &event);

void cleanUp(Rectangle *rectangleArray, Text* rectangleText, int size);

// Sign-in window function
// Connections window function
// Hangman window function

bool isLetter(char &inputChar);


int signIn ();
bool signInPoll(std::string signInFields[], SDL_Event &event);

// Must have this binary search function in the header file for some reasons (idk it didn't work otherwise :) )


template <typename Type>
int binarySearch (std::vector<Type> &array, Type &key, int low, int high) 
{
    int middle = (low + high) / 2;
    // Case where key is NOT in data set
    /* There will be no difference in middle if low and high are separated by one
    This happens when the whole array has been searched through for the key value */
    if (low > high) {
        return -(middle + 1);
    }
    // Binary Search where key is in data set
    // Lower Half
    else if (key < array[middle]) {
        // Look at the lower half
        // High changes, low does not
        return binarySearch(array, key, low, middle - 1);
    }
    // Upper Half
    else if (key > array[middle]) {
        // Look at the upper half
        // Low changes, high does not
        return binarySearch(array, key, middle + 1, high);
    }
    // Is Half
    else /*(key == array[middle])*/ {
        // The middle number IS the key
        return middle;
    }
}

#endif