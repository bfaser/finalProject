#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"
#include "..\headers\games\wordle.hpp"
#include "..\headers\games\hangman.hpp"


// Convert this into the sign-in page ? 
// It could look pretty cool to make the background of every page the Whitworth logo...watermark???
int mainMenu () {
  // Create the window object and define the width / height of window
  int windowWidth = 640, windowHeight = 480;
  Window window("S\'GO BUCS", windowWidth, windowHeight);
  SDL_Color grey = {140,140,140,255};
  SDL_Event event;

  // Create the Whitworth flag logo and center it
  int position[2] = {windowWidth / 2, windowHeight / 2 - 75};
  int buttonPosition[2] =  {windowWidth / 2, windowHeight - 50}; // Center: x = 320, y = 430
  Rectangle rectangle(300, 300, position, "assets/whitworth-university_logo.png");

  // Wordle Button
  Rectangle wordleButton (200, 50, buttonPosition, grey);
  Text wordleButtonText (Window::renderer, 60, "Wordle", {0, 0, 0, 255});
  wordleButtonText.linkRect(wordleButton);
  wordleButton.setButton(true, event);

  // Hangman Button
  buttonPosition[1] -= 75;
  Rectangle hangmanButton (200, 50, buttonPosition, grey);
  Text hangmanButtonText (Window::renderer, 60, "Hangman", {0, 0, 0, 255});
  hangmanButtonText.linkRect(hangmanButton);
  hangmanButton.setButton(true, event);

  // Text "Whitworth Pirates" 
  Text text(Window::renderer, 30, "Whitworth Pirates", {0, 0, 0, 255});

  // Generic Background color to fill the screen with after every iteration of the loop
  SDL_Color backgroundColor = {255,255,255,255};

  int size = 2;
  Rectangle buttonArray[size] = {wordleButton, hangmanButton};
  Text buttonTexts[size] = {wordleButtonText, hangmanButtonText};
  // Main loop for display -> Can define more ways to close application in the window class pollEvents() function
  while (!window.isClosed()) {
    // Take in the user inputs -> poll events
    SDL_SetWindowTitle(window.windowObj(), "Main Menu");
    pollEventMenu(window, buttonArray, event);

    // Present the renderer with whatever here
    rectangle.draw(event);
    text.display(windowWidth / 2 , windowHeight / 2 - 150, Window::renderer);

    // Draw Button and the text on button
    displayMenu(buttonArray, buttonTexts, size, event);

    // Draw the presented items first, then add background behind them using widow.clear(SDL_Color background-color) function
    window.clear(backgroundColor);
  }
  return 0;
}


// Polls the events of the Main Menu
void pollEventMenu (Window &window, Rectangle buttonArray[], SDL_Event &event) {
  // Conditionals to decode inputs (button presses, keystrokes, etc)
  if (SDL_PollEvent(&event)) {
    // Closing the window if escape or the window 'x' is pressed
    window.pollEvents(event);
    // Logic for different buttons
    if (buttonArray[0].isClicked(event)) {
      // Wordle Button Pressed
      Wordle wordleInstance;
      wordleInstance.play(window);
      // window.close();
    }
    else if (buttonArray[1].isClicked(event)) {
      // Hangman Button Pressed
      Hangman hangmanInstance;
      hangmanInstance.play(window);
    }
  }
}

// Main Menu Function for drawing all buttons to the screen
void displayMenu (Rectangle buttonsArray[], Text buttonTexts[], int size, SDL_Event &event) {
  for (int i = 0; i < size; i++) {
    if (buttonsArray != nullptr) {buttonsArray[i].draw(event);}
    if (buttonTexts != nullptr) {buttonTexts[i].display();}
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

void gridCreate(Window &window, int placement[], std::vector<SDL_Color> &color, Rectangle rectangleArray[], bool multiBuffer, Text rectangleText[]) {
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
    for (int c = 0; c < placement[1]; c++) {
      // Calculate the X component of each rectangle, with respect to the buffer style
      positionX = buffer + (width / 2) + (c*width);
      if (multiBuffer) {positionX = placement[4] + (width / 2) + c*(width + placement[5]);}
      rectangleArray[r*columns + c].define(width, height, positionX, positionY, color[r*columns + c]);
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
  SDL_Color color - color of the text
  int charLimit - character limit for the textboxes
*/

void writeTexts (Text textArray[], std::vector<std::string> &stringArray, int dimensions[], SDL_Color color, int charLimit) {
  int rows = dimensions[0];
  int columns = dimensions[1];
  std::string letter;
  for (int r = 0; r < rows; r++) {
    std::string bufferedMessage = checkStringLength (stringArray[r], columns);
    for (int c = 0; c < columns; c++) {
      std::string string = "";
      string = bufferedMessage[c];
      textArray[r*columns + c].defineObj(Window::renderer, 60, string, color, charLimit);
    }
  }
}

// Converts an input character to its lower case equivalent if it is uppercase
char lower (char input) {
  if (input < 'a'){
      input += 'a' - 'A';
  }
  return input;
}

// Checks the length of the input string
// If the string is shorter than the desired length, charLength, a whitespace character is appended
std::string checkStringLength (std::string inputString, int charLength) {
  while ((int)inputString.length() <= charLength) {
    inputString.append(" ");
  }
  return inputString;
}

// Calls the destructor of the given rectangleArray and rectangleText objects
// This was in response to a memory leak that happens while games are being played
void cleanUp(Rectangle* rectangleArray, Text* rectangleText, int size) {
  for (int i = 0; i < size; i++) {
    rectangleArray[i].~Rectangle();
    rectangleText[i].~Text();
  } 
}

// Checks if an input character is a letter
// Simultaneously converts any input character to its lowercase equivalent if appropriate
bool isLetter(char &inputChar) {
    inputChar = lower(inputChar);

    if ('a' <= inputChar && inputChar <= 'z') {
        return true;
    }
    return false;
}

// UNFINISHED AND UNIMPLEMENTED



// Sign in window
int signIn () {
  int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
  Window window ("Sign-In Page", WINDOW_WIDTH,WINDOW_HEIGHT);
  SDL_Event event;
  std::string textInputs[2] = {""};
  // textInputs[0] -> User name field
  // textInputs[1] -> Password field

  bool running = true;
  SDL_Color backgroundColor = {255,255,255,255};
  SDL_StartTextInput();
  while (running) {
    running  = signInPoll(textInputs, event);
    window.clear(backgroundColor);
  }
  SDL_StopTextInput();
  return 0;
}


// Events polling (any input to the keyboard or mouse) for the sign in page
bool signInPoll(std::string signInFields[], SDL_Event &event) {
  if (SDL_PollEvent(&event)) {
      switch (event.type)
      {
      case SDL_TEXTINPUT:

      case SDL_QUIT:
        return false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          return false;
        }
        break;
      default:
        return true;
        break;
      }
    }
    return true;
}