#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../SDL2/include/SDL2/SDL.h"
#include "../headers/games/wordle.hpp"
#include "../headers/graphics.hpp"


// Initializes the words vectors inside the wordle class
void Wordle::initWordsVec() {
    // Loads the valid words text file into a vector
    std::ifstream textFile;
    textFile.open("assets/valid-wordle-words.txt");
    
    std::string word;
    while (std::getline(textFile, word)) {
        validWords.emplace_back(word);
    }

    textFile.close();
    // Loads the possible secret words into a vector and selects one
    std::vector<std::string> commonWords;
    textFile.open("assets/common-words.txt");
    while (std::getline(textFile, word)) {
        commonWords.emplace_back(word);
    }
    textFile.close();
    int index = rand() % commonWords.size();
    secretWord = commonWords[index];
}


// Initializes the wordle class with a new SDL event, new tries and sets up the rectangle colors
Wordle::Wordle()
{
    event = new SDL_Event;
    currentTry = 0;
    if (validWords.size() == 0) {
        initWordsVec();
    }
    for (int i = 0; i < ((int)secretWord.length() * maxAttempts); i++) {
        color.push_back({140,140,140,255});
    }
    for (int i = 0; i < maxAttempts; i++) {
        guessedWords.push_back("");
    }
    std::cout << secretWord << std::endl;
}

// Window for Wordle game
void Wordle::play (Window &window) {
    // Set up the window, wordle grid and text objects (preprocessing)
    running = true;
    SDL_SetWindowTitle(window.windowObj(), "Whit-Wordle");
    Text wordleTitle(Window::renderer, 40, "Whit-Wordle", {255,255,255,255});

    // Set up the wordle cells
    int topBuffer = 100; // In pixels, specifies space from top of window
    int bottomBuffer = 1; // In pixels, specifies space from bottom of window
    int sideBuffer = 50; // In pixels, specifies space from the sides of the window, symmetric
    int cellBuffer = 1; // In pixels, specifies the separation between cells both horizontally and vertically

    // Array wrapping the grid specs and the buffering information
    int placement[6] = {maxAttempts, (int)secretWord.length(), topBuffer, bottomBuffer, sideBuffer, cellBuffer};
    // Rectangle objects to be converted into wordle grid
    Rectangle wordleCells[maxAttempts * (int)secretWord.length()];
    // Text objects to hold the wordle information
    Text wordleText[maxAttempts * (int)secretWord.length()];
    
    SDL_StartTextInput();
    // Main loop
    while (running) {
        running = pollEvents();

        // Populating the text array with the corresponding characters for wordle
        writeTexts(wordleText, guessedWords, placement);
        gridCreate(window, placement, color, wordleCells , true, wordleText);

        // Displaying the boxes for the wordle input fields
        displayMenu (wordleCells,wordleText,(maxAttempts * (int)secretWord.length()), *event);
        
        // Render the title of the game over the boxes (ensure that title doesn't get covered by the wordle boxes)
        wordleTitle.display(window.getWidth() / 2, 50, Window::renderer);

        endingState(window);

        // Draw everything in the render buffer and clear the background with generic color
        window.clear(backgroundColor);

        // Check if either the win or lose conditions are true
        if (endState != "") {
            SDL_Delay(3000);
        }

        // This is used to destroy the objects, ensures no memory leak
        cleanUp(wordleCells, wordleText, (maxAttempts * (int)secretWord.length()));
    }

    // Clean-up after
    SDL_StopTextInput();
    return;
}


// Poll Events for the Wordle Game loop
// Any input to the keyboard or mouse is considered an event
bool Wordle::pollEvents() {
    if (SDL_PollEvent(event)) {
        // Text Input
        switch (event->type) {
            case SDL_QUIT:
            return false;
            break;
            case SDL_TEXTINPUT:
            // If its any character other than return or delete, add to the string (if less than 5 characters long)
            if (guessedWords[currentTry].length() < secretWord.length() && isLetter(*event->text.text)) {
                guessedWords[currentTry] += lower(*event->text.text);
            }
            case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
            case  SDLK_BACKSPACE:
            //  If the key is backspace, delete last character
                if (guessedWords[currentTry].length() > 0) {
                    guessedWords[currentTry] = guessedWords[currentTry].substr(0, guessedWords[currentTry].length() - 1);
                }
                break;
            case SDLK_RETURN:
            // If key is enter key, check using the submission function
                if (guessedWords[currentTry].length() >= secretWord.length()) {
                // Check function
                bool valid = submit(guessedWords[currentTry]);

                if (secretWord == guessedWords[currentTry]) {
                    // Display Win Screen
                    endState = "win";
                    // Stop further text input
                    SDL_StopTextInput();
                    return false;
                }
                else if (valid) {
                    // Increment the current try
                    currentTry++;
                    if (currentTry >= maxAttempts) {
                    endState = "lose";
                    return false;
                    }
                }
                }
                break;
                case SDLK_ESCAPE:
                return false;
                break;
            default:
                break;
            }
            default:
            break;
        }
        }
        return true;
}


// Submission check function for the wordle game
// Called when enter key is hit and the row contains 5 characters
bool Wordle::submit(std::string &enteredWord) {
    // Check if word is valid
    int isValid = binarySearch(validWords, enteredWord, 0, validWords.size() - 1);
    if (isValid < 0) {
        std::cout << "Invalid Word" << std::endl;
        return false;
    }

    // Set up the colors for the different scenarios 
    SDL_Color red = {202, 52, 51, 255};
    SDL_Color orange = {245, 224, 80,255};
    SDL_Color green = {123, 182, 97,255}; 
    std::string word  = secretWord;
    for (int i = 0; i < (int)secretWord.length(); i++) {
        int index = (int)secretWord.find(enteredWord[i]);
        // Correct Letter with Correct Placement
        if (secretWord[i] == enteredWord[i]) {
        color[currentTry*(int)secretWord.length() + i] = green;
        word.erase(index,0);
        }
        // Correct Letter with Incorrect Placement
        else if (index >= 0) {
        color[currentTry*(int)secretWord.length() + i] = orange;
        word.erase(index,0);
        }
        // Incorrect Letter entirely
        else {
        color[currentTry*(int)secretWord.length() + i] = red;
        }
    }
    return true;
}

// Displays the win or lose screen overlayed on the game
void Wordle::endingState(Window &window) {
    if (running) {
        return;
    }
    if (endState == "") {
        return;
    }
    if (endState == "win") {
        highScore = (maxAttempts - currentTry)*100;
        winScreen(window, "Score: " + std::to_string(highScore));
        return;
    }
    loseScreen(window, "Secret Word: " + secretWord);
    return;
}