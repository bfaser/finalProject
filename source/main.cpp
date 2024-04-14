#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"

// Refactor so there is a wordle class / implementation class
// Basically, clean up the main function so that it is as simple as possible

int main () {
  std::string placeHolder = "     ";
  std::string test = "WhitW";
  std::string fiveLetter[5] = {test, placeHolder, placeHolder, placeHolder, placeHolder};

  // showGraphics();
  showWordle(fiveLetter);
}

// Basic to-do list for immediate future

// Work on adding rectangle bounding box & mouse hover effect
// Refactor code in showWordle function to make it more reusable (functionalize) 
// Create a button class and dynamic display (show the keyboard inputs on GUI)

// The wordleWordsList will be populated at the program's initialization (passed around)

/* bool validWord (std::string submittedWord, list<string>  wordleWordsList) {
  // char count = 1st char
  while (charCount < submittedWord.length) {
    for (int i = 0; i < wordleWordsList.length; i++) {
      // search through the 15,000 words for the submittedWord's (charCount) char in wordleWordsList
      // pop off words that dont match the letter from back
    }
    // increment charCount
    // Move onto comparing the next letter
  }

  if (list<strings> != empty) {
    return true;
  }
  return false;
}

bool isSecretWord (std::string secretWord, std::string submittedWord) {
  return (submittedWord == secretWord);
}


***ON SUBMISSION***
if (!validWord) {
  // dont check if it is the submitted word
  // signal error and allow user to resubmit their guessed word
  // dont use a guess
  return (dont continue through rest of program)
}

if (!isSecretWord) {
  // check for matching characters in incorrect positions (orange cells)
    // check for matching characters in the correct positions (green cells -> overwrite the orange cell)
  // return this to the screen to be rendered
}
(its the secret word so congratulations!) -> victory screen and score(?)
*/