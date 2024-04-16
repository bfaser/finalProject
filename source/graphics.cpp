#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"


// Convert this into the sign-in page ? 
// It could look pretty cool to make the background of every page the Whitworth logo...watermark???
int showGraphics () {
  // Create the window object and define the width / height of window
  int windowWidth = 640, windowHeight = 480;
  Window window("S\'GO BUCS", windowWidth, windowHeight);
  // Define a general event;
  SDL_Event event;
  SDL_Color grey = {140,140,140,255};

  // Create the Whitworth flag logo and center it
  int position[2] = {windowWidth / 2, windowHeight / 2};
  int buttonPosition[2] =  {windowWidth / 2, windowHeight - 50}; // Center: x = 320, y = 430
  Rectangle rectangle(400, 400, position, "assets/whitworth-university_logo.png");
  Rectangle button (200, 50, buttonPosition, grey);
  Text buttonText (Window::renderer, 60, "Button", {0, 0, 0, 255});
  buttonText.linkRect(button);
  button.setButton(true);

  // Text "Whitworth Pirates" 
  Text text(Window::renderer, 30, "Whitworth Pirates", {0, 0, 0, 255});

  // Generic Background color to fill the screen with after every iteration of the loop
  SDL_Color backgroundColor = {255,255,255,255};

  // Main loop for display -> Can define more ways to close application in the window class pollEvents() function
  while (!window.isClosed()) {
    // Take in the user inputs -> poll events
    if (SDL_PollEvent(&event)) {
      window.pollEvents(event);
      if (button.isClicked(event)) {
        // Individual Button Clicking function calls here
        std::cout<<"Clicked Button!\n";
      }
    }
    // Present the renderer with whatever here
    rectangle.draw();
    text.display(windowWidth / 2 - 20, windowHeight / 2 - 150, Window::renderer);

    // Draw Button and the text on button
    button.draw();
    buttonText.display();

    // Draw the presented items first, then add background behind them using widow.clear(SDL_Color background-color) function
    window.clear(backgroundColor);
  }
  return 0;
}

// Rework so that the input to the showWordle function is checked every frame and updated
// This rework will make it MUCH easier to get the typed letters to appear on the screen
// Add comments to this function as you refactor and rework -> it will help a TON in the long run
int showWordle (std::string fiveLetter[]) {
  // Initialize Window named "Wordle" with variables windowWidth and windowHeight
  int windowWidth = 640, windowHeight = 480;
  Window wordleWindow("Wordle", windowWidth, windowHeight);
  SDL_Event event;
  
  // Separate SDL_Colors into their own cpp file? That way they are all unified
  SDL_Color grey = {140,140,140,255}; // Color grey in r,g,b,a values
  SDL_Color black = {0, 0, 0, 255};
  
  // Components to the placement vector, specifying rows, columns and buffers
  int rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer; 
  rows = 5; // Number of  cells stacked vertically
  columns = 5; // Number of cells per row
  topBuffer = 40; // In pixels, specifies space from top of window
  bottomBuffer = 1; // In pixels, specifies space from bottom of window
  sideBuffer = 20; // In pixels, specifies space from the sides of the window, symmetric
  cellBuffer = 1; // In pixels, specifies the separation between cells both horizontally and vertically

  // Wrapping the above specifications into a single array to pass into the gradCreate function
  int placement[6] = {rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer};
  // Generates a generic rectangle object, will be defined later using the gridCreate function
  Rectangle rectangleArray[rows*columns];

  // Generic text array
  Text rectangleText[rows*columns];
  std::string letter;
  
  // Populating the text array with the corresponding characters for wordle
  for (int i = 0; i < (rows*columns); i++) {
    letter = "";
    char l = fiveLetter[i / rows][i % rows];
    letter += l;
    rectangleText[i].defineObj(Window::renderer, 60, letter, black, 1);
  }


  
  SDL_Color backgroundColor = {100,100,100,255};
  while (!wordleWindow.isClosed()) {

      if (SDL_PollEvent(&event)) {
        wordleWindow.pollEvents(event);
      }

      gridCreate(wordleWindow, placement, grey, rectangleArray , true, rectangleText);
      for (int i = 0; i < (rows*columns); i++) {
        rectangleArray[i].draw();
        rectangleText[i].display();
      }
      wordleWindow.clear(backgroundColor);
  }
  return 0;
}

/*
Window:: window
  Window to render grid onto, also provides the window width & height

int placement[3-6] = {rows, columns, buffer(s)}

int color[4] = {r,g,b,a}

rectArray[rows * columns] 

bool multiBuffer - buffers expands to top buffer, bottom buffer, side buffers, and between-cell buffer

*/

// Add comments to this function so that it is easier to reuse (e.g. connections renderer)

void gridCreate(Window &window, int placement[], SDL_Color color, Rectangle rectangleArray[], bool multiBuffer, Text rectangleText[]) {
  // Placeholder variables to make placement elements clearer
  int width, height, rows, columns,buffer;
  rows = placement[0];
  columns = placement[1];
  buffer = placement[2];
  // Checks if the individual buffers flag is true
  if (multiBuffer) {
    // Accounts for the modified width and heights of the cells being separated
    int topBuffer, bottomBuffer, sideBuffer, cellBuffers;
    topBuffer = buffer;
    bottomBuffer = placement[3];
    sideBuffer = placement[4];
    cellBuffers = placement[5]; 

    width = (window.getWidth() - (2*sideBuffer + columns*cellBuffers)) / columns;
    height = (window.getHeight() - (topBuffer + bottomBuffer + rows*cellBuffers)) / rows;
  }
  else {
    // Default case where all cells are edge-to-edge
    width = (window.getWidth() - 2*buffer) / columns;
    height = (window.getHeight() - 2*buffer) / rows;
  }
  
  // X and Y positions of each rectangle center ; individual rectangle positions are saved within rectangle object
  int positionX, positionY;

  // Loop over the rows (top -> bottom)
  for (int r = 0; r < placement[0]; r++) {
    // Calculate the Y component of rectangles in the row, taking into account the different buffer types
    positionY = buffer + (height / 2) + (r*height);
    if (multiBuffer) {positionY += r*placement[5];}
    // Loop over each rectangle in rows (left -> right)
    for (int c = 0; c < columns; c++) {
      // Calculate the X component of each rectangle, with respect to the buffer style
      positionX = buffer + (width / 2) + (c*width);
      if (multiBuffer) {positionX = placement[4] + (width / 2) + c*(width + placement[5]);}
      rectangleArray[r*columns + c].define(width, height, positionX, positionY, color);
      // If there is a text object corresponding to each rectangle, link text to the corresponding rectangle 
      if (rectangleText != nullptr) {rectangleText[r*columns + c].linkRect(rectangleArray[r*columns + c]);}      
    }      
  }
}

/*
  Text textArray[rows][columns] - array of text objects that need to be defined
  std::stringArray[rows] - string of values to be linked to the text objects
    the size of each entry in the stringArray will be of length (columns) for wordle specifically
  int dimensions[2] - gives the rows (1st entry) and the columns (2nd entry) 
*/

void writeTexts (Text textArray[], std::string stringArray[], int dimensions[]);