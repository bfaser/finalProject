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

  // Create the Whitworth flag logo and center it
  int position[2] = {windowWidth / 2, windowHeight / 2};
  Rectangle rectangle(400, 400, position, "assets/whitworth-university_logo.png");

  // Text saying "Whitworth Pirates" 
  Text text(Window::renderer, "assets/times.ttf", 30, "Whitwoth Pirates", {0, 0, 0, 255});

  // Generic Background color to fill the screen with after every iteration of the loop
  SDL_Color backgroundColor = {255,255,255,255};

  // Main loop for display -> Can define more ways to close application in the window class pollEvents() function
  while (!window.isClosed()) {
    // Take in the user inputs -> define more under window class
    pollEvents(window);
    // Present the renderer with whatever here
    rectangle.draw();
    text.display(windowWidth / 2 - 20, windowHeight / 2 - 150, Window::renderer);

    // Draw the presented items first, then add background behind them using widow.clear(SDL_Color background-color) function
    window.clear(backgroundColor);
  }
  return 0;
}

// Rework so that the input to the showWordle function is checked every frame and updated
// This rework will make it MUCH easier to get the typed letters to appear on the screen
// Add comments to this function as you refactor and rework -> it will help a TON in the long run
int showWordle (std::string fiveLetter[]) {
  int windowWidth = 640, windowHeight = 480;
  Window wordleWindow("Wordle", windowWidth, windowHeight);

  int rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer; 
  SDL_Color grey = {140,140,140,255}; // Color grey in r,g,b,a values
  SDL_Color black = {0, 0, 0, 255};
  rows = 5; 
  columns = 5;
  topBuffer = 40;
  bottomBuffer = 1;
  sideBuffer = 20;
  cellBuffer = 1;
  int placement[6] = {rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer};
  Rectangle rectangleArray[rows*columns];


  Text rectangleText[rows*columns];
  std::string letter;
  
  for (int i = 0; i < (rows*columns); i++) {
    letter = "";
    char l = fiveLetter[i / rows][i % rows];
    letter += l;
    rectangleText[i].defineObj(Window::renderer, "assets/times.ttf", 30, letter, black, 1);
  }


  gridOfRects(wordleWindow, placement, grey, rectangleArray, true, rectangleText);
  SDL_Color backgroundColor = {100,100,100,255};
  while (!wordleWindow.isClosed()) {
      pollEvents(wordleWindow);
      for (int i = 0; i < (rows*columns); i++) {
        rectangleArray[i].draw();
        rectangleText[i].display();
      }
      wordleWindow.clear(backgroundColor);
  }
  return 0;
}

void pollEvents(Window &window) {
  SDL_Event event;

  if (SDL_PollEvent(&event)) {

    window.pollEvents(event);
  }
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

void gridOfRects(Window &window, int placement[], SDL_Color color, Rectangle rectangleArray[], bool multiBuffer, Text rectangleText[]) {
  int width, height, rows, columns,buffer;
  rows = placement[0];
  columns = placement[1];
  buffer = placement[2];
  if (multiBuffer) {
    int topBuffer, bottomBuffer, sideBuffer, cellBuffers;
    topBuffer = buffer;
    bottomBuffer = placement[3];
    sideBuffer = placement[4];
    cellBuffers = placement[5]; 

    width = (window.getWidth() - (2*sideBuffer + columns*cellBuffers)) / columns;
    height = (window.getHeight() - (topBuffer + bottomBuffer + rows*cellBuffers)) / rows;
  }
  else {
    width = (window.getWidth() - 2*buffer) / columns;
    height = (window.getHeight() - 2*buffer) / rows;
  }
  
  int positionX, positionY;

  for (int r = 0; r < placement[0]; r++) {
    positionY = buffer + (height / 2) + (r*height);
    if (multiBuffer) {positionY += r*placement[5];}
    for (int c = 0; c < columns; c++) {
      positionX = buffer + (width / 2) + (c*width);
      if (multiBuffer) {positionX = placement[4] + (width / 2) + c*(width + placement[5]);}
      rectangleArray[r*columns + c].define(width, height, positionX, positionY, color);
      rectangleText[r*columns + c].linkRect(rectangleArray[r*columns + c]);
    }      
  }
}
