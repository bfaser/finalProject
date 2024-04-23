#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"
#include "..\headers\SDL2\window.hpp"
#include "..\headers\SDL2\rectangle.hpp"
#include "..\headers\SDL2\text.hpp"
#include "..\headers\games\wordle.hpp"


// Convert this into the sign-in page ? 
// It could look pretty cool to make the background of every page the Whitworth logo...watermark???
int showGraphics () {
  // Create the window object and define the width / height of window
  int windowWidth = 640, windowHeight = 480;
  Window window("S\'GO BUCS", windowWidth, windowHeight);
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
    pollEvent(window, &button);

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

void pollEvent (Window &window, Rectangle buttonArray[]) {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
      window.pollEvents(event);
      if (buttonArray[0].isClicked(event)) {
        // Individual Button Clicking function calls here
        std::cout<<"Clicked Button!\n";
      }
    }
}

// Rework so that the input to the showWordle function is checked every frame and updated
// This rework will make it MUCH easier to get the typed letters to appear on the screen
// Add comments to this function as you refactor and rework -> it will help a TON in the long run
int showWordle (Wordle &wordleInstance) {
  // Initialize Window named "Wordle" with variables windowWidth and windowHeight
  int windowWidth = 640, windowHeight = 480;
  Window wordleWindow("Wordle", windowWidth, windowHeight);
    
  // Components to the placement vector, specifying rows, columns and buffers
  int rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer; 
  rows = 5; // Number of  cells stacked vertically
  columns = 5; // Number of cells per row
  topBuffer = 40; // In pixels, specifies space from top of window
  bottomBuffer = 1; // In pixels, specifies space from bottom of window
  sideBuffer = 50; // In pixels, specifies space from the sides of the window, symmetric
  cellBuffer = 1; // In pixels, specifies the separation between cells both horizontally and vertically

  // Wrapping the above specifications into a single array to pass into the gradCreate function
  int placement[6] = {rows, columns, topBuffer, bottomBuffer, sideBuffer, cellBuffer};
  // Generates a generic rectangle object, will be defined later using the gridCreate function
  Rectangle rectangleArray[rows*columns];

  // Generic text array
  Text rectangleText[rows*columns];
  std::string letter;
  int trial = 0;
  
  
  SDL_StartTextInput();
  SDL_Color backgroundColor = {100,100,100,255};
  while (!wordleWindow.isClosed()) {
      pollWordleEvents(wordleWindow, trial, wordleInstance);

      // Populating the text array with the corresponding characters for wordle
      writeTexts(rectangleText, wordleInstance.guessedWords, placement);
      gridCreate(wordleWindow, placement, wordleInstance.color, rectangleArray , true, rectangleText);

      for (int i = 0; i < (rows*columns); i++) {
        rectangleArray[i].draw();
        rectangleText[i].display();
      }

      wordleWindow.clear(backgroundColor);
      cleanUpWordle(rectangleArray, rectangleText, (rows*columns));     
  }
  SDL_StopTextInput();
  return 0;
}

void pollWordleEvents (Window &window, int& trial, Wordle &wordleInstance) {
  SDL_Event event;
  std::string *inputString = wordleInstance.guessedWords;
  if (SDL_PollEvent(&event)) {
      window.pollEvents(event);
      // Text Input
      switch (event.type) {
        case SDL_TEXTINPUT:
        // If its any character other than return or delete, add to the string (if less than 5 characters long)
          if (inputString[trial].length() < 5) {
            inputString[trial] += lower(*event.text.text);
          }
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
          case  SDLK_BACKSPACE:
          //  If the key is backspace, delete last character
            if (inputString[trial].length() > 0) {
              inputString[trial] = inputString[trial].substr(0, inputString[trial].length() - 1);
            }
            break;
          case SDLK_RETURN:
          // If key is enter key, check using the submission function
            if (inputString[trial].length() >= 5) {
              // Check function
              bool valid = wordleSubmit(wordleInstance, inputString[trial], trial);

              // update the color array
              if (valid) {
                trial++;
              }
            }
          default:
            break;
          }
      }
    }
    window.pollEvents(event);
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

void gridCreate(Window &window, int placement[], SDL_Color color[], Rectangle rectangleArray[], bool multiBuffer, Text rectangleText[]) {
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

void writeTexts (Text textArray[], std::string stringArray[], int dimensions[], SDL_Color color, int charLimit) {
  int rows = dimensions[0];
  int columns = dimensions[1];
  std::string letter;
  for (int r = 0; r < rows; r++) {
    std::string bufferedMessage = checkStringLength (stringArray[r], 5);
    for (int c = 0; c < columns; c++) {
      std::string string = "";
      string = bufferedMessage[c];
      textArray[r*columns + c].defineObj(Window::renderer, 60, string, color, charLimit);
    }
  }
}

char lower (char input) {
  if (input < 97){
      input += 'a' - 'A';
  }
  return input;
}

std::string checkStringLength (std::string inputString, int charLength) {
  while ((int)inputString.length() <= charLength) {
    inputString.append(" ");
  }
  return inputString;
}

bool wordleSubmit (Wordle &wordleInstance, std::string &enteredWord, int &trial) {
  std::vector<std::string> words = wordleInstance.getWordsVec();
  int isValid = binarySearch(enteredWord, words);
  SDL_Color red = {255,40,0,255};
  SDL_Color orange = {255,165,0,255};
  SDL_Color green = {80,200,120,255}; 
  if (isValid < 0) {
    return false;
  }
  std::string secretWord  = wordleInstance.getSecretWord();
  for (int i = 0; i < 5; i++) {
    int index = (int)secretWord.find(enteredWord[i]);
    if (index >= 0) {
      wordleInstance.color[trial*5 + i] = orange;
      secretWord.erase(index,1);
    }
    else {
      wordleInstance.color[trial*5 + i] = red;
    }

    if (wordleInstance.getSecretWord()[i] == enteredWord[i]) {
      wordleInstance.color[trial*5 + i] = green;
    }
  }
  return true;
} 

template <typename Type>
// Binary Seach function called in Main()
int binarySearch (Type &key, std::vector<Type> &array) {
    return binarySearch(array, key, 0, array.size() - 1);
}

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

void cleanUpWordle(Rectangle* rectangleArray, Text* rectangleText, int size) {
  for (int i = 0; i < size; i++) {
    rectangleArray[i].~Rectangle();
    rectangleText[i].~Text();
  } 
}