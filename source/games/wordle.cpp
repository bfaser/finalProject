#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../SDL2/include/SDL2/SDL.h"
#include "../headers/games/wordle.hpp"
#include "../headers/graphics.hpp"

void Wordle::initWordsVec() {
    std::ifstream textFile;
    textFile.open("assets/valid-wordle-words.txt");
    
    std::string word;
    while (std::getline(textFile, word)) {
        validWords.emplace_back(word);
    }

    textFile.close();

    int index = rand() % 14855;
    secretWord = validWords[index];
}

Wordle::Wordle()
{
    maxAttempts = 5;
    highScore = 0;
    running = false;
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
        displayMenu (wordleCells,wordleText,(maxAttempts * (int)secretWord.length()));
        
        // Render the title of the game over the boxes (ensure that title doesn't get covered by the wordle boxes)
        wordleTitle.display(window.getWidth() / 2, 50, Window::renderer);

        // Draw everything in the render buffer and clear the background with generic color
        window.clear(backgroundColor);

        // This is used to destroy the objects, ensures no memory leak
        cleanUp(wordleCells, wordleText, (maxAttempts * (int)secretWord.length()));
    }

    // Clean-up after
    SDL_StopTextInput();

    cleanUp(wordleCells, wordleText, (maxAttempts * (int)secretWord.length()));
    return;
}

bool Wordle::pollEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        // Text Input
        switch (event.type) {
            case SDL_QUIT:
            return false;
            break;
            case SDL_TEXTINPUT:
            // If its any character other than return or delete, add to the string (if less than 5 characters long)
            if (guessedWords[currentTry].length() < secretWord.length() && isLetter(*event.text.text)) {
                guessedWords[currentTry] += lower(*event.text.text);
            }
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case  SDLK_BACKSPACE:
            //  If the key is backspace, delete last character
                if (guessedWords[currentTry].length() > 0 && secretWord != guessedWords[currentTry]) {
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
                    std::cout << "YOU WON!!!" << std::endl;
                    // Stop further text input
                    SDL_StopTextInput();
                }
                else if (valid) {
                    currentTry++;
                    if (currentTry >= maxAttempts) {
                    std::cout << "YOU LOST" << std::endl;
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

bool Wordle::submit(std::string &enteredWord) {
    int isValid = binarySearch(validWords, enteredWord, 0, validWords.size() - 1);
    SDL_Color red = {255,40,0,255};
    SDL_Color orange = {255,165,0,255};
    SDL_Color green = {80,200,120,255}; 
    if (isValid < 0) {
        std::cout << "Invalid Word" << std::endl;
        return false;
    }
    std::string word  = secretWord;
    for (int i = 0; i < (int)secretWord.length(); i++) {
        int index = (int)secretWord.find(enteredWord[i]);
        if (secretWord[i] == enteredWord[i]) {
        color[currentTry*(int)secretWord.length() + i] = green;
        word.erase(index,0);
        }
        else if (index >= 0) {
        color[currentTry*(int)secretWord.length() + i] = orange;
        word.erase(index,0);
        }
        else {
        color[currentTry*(int)secretWord.length() + i] = red;
        }
    }
    return true;
}