#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"

// Refactor so there is a wordle class / implementation class
// Basically, clean up the main function so that it is as simple as possible

int main () {
  std::string placeHolder = "     ";
  std::string fiveLetter[5] = {placeHolder, placeHolder, placeHolder, placeHolder, placeHolder};

  showGraphics();
  // showWordle(fiveLetter);
}

// Basic to-do list for immediate future

// Work on adding rectangle bounding box & mouse hover effect
// Refactor code in showWordle function to make it more reusable (functionalize) 
// Create a button class and dynamic display (show the keyboard inputs on GUI)