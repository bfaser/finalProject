#include <string>
#include "..\headers\graphics.hpp"
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"

int showGraphics () {
  Window window("S\'GO BUCS", 640, 480);
  int position[2] = {640 / 2, 480 / 2};
  Rectangle rectangle(400, 400, position, "assets/whitworth-university_logo.png");
  Text text(Window::renderer, "assets/times.ttf", 30, "Whitwoth Pirates", {0, 0, 0, 255});

  SDL_Color backroundColor = {255,255,255,255};

  while (!window.isClosed()) {
      pollEvents(window);
      rectangle.draw();
      text.display(600 / 2, 125, Window::renderer);
      window.clear(backroundColor);
  }
  return 0;
}


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
  SDL_Color backroundColor = {100,100,100,255};
  while (!wordleWindow.isClosed()) {
      pollEvents(wordleWindow);
      for (int i = 0; i < (rows*columns); i++) {
        rectangleArray[i].draw();
        rectangleText[i].display();
      }
      wordleWindow.clear(backroundColor);
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
