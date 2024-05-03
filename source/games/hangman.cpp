#include <iostream>
#include <fstream>
#include "../headers/games/hangman.hpp"
#include "../headers/SDL2/rectangle.hpp"
#include "../headers/graphics.hpp"

Hangman::Hangman() {
    if (!initialize()) {
        std::cerr << "Error loading Hangman\n";
    }
}

bool Hangman::initialize() {
    currentTry = 0;
    event = new SDL_Event;
    std::vector<std::string> hangmanWords;
    std::string word;
    std::ifstream readFile("assets/hangmanWords.txt");

    while (getline(readFile, word)) {
        hangmanWords.emplace_back(word);
    }
    secretWord = hangmanWords[rand() % hangmanWords.size()];
    readFile.close();

    if (secretWord.length() == 0) {
        std::cerr << "Error choosing secret word\n";
        return false;
    }

    SDL_Color BLACK = {0,0,0,255};
    for (int i = 0; i < (int)secretWord.length(); i++) {
        letterColors.emplace_back(BLACK);
    }
    if (letterColors.size() != secretWord.length()) {
        std::cerr << "Failed to create box colors\n";
        return false;
    }

    characters = "qwertyuiopasdfghjklzxcvbnm";
    if (characters.length() != 26) {
        std::cerr << "Failed to create characters array\n";
        return false;
    }

    return true;
}

void Hangman::play (Window &window) {
    running = true;
    SDL_Color WHITE = {255,255,255,255};

    SDL_SetWindowTitle(window.windowObj(), "Whit-Wordle");

    std::cout << secretWord << std::endl;

    // Set up the secret word blank boxes

    int topBuffer = window.getHeight() / 2 - 30; // In pixels, specifies space from top of window
    int bottomBuffer = window.getHeight() / 3 + 45; // In pixels, specifies space from bottom of window
    int sideBuffer = 50; // In pixels, specifies space from the sides of the window, symmetric
    int cellBuffer = 1; // In pixels, specifies the separation between cells both horizontally and vertically

    int dimensions[6] = {1,(int)secretWord.length(), topBuffer, bottomBuffer, sideBuffer, cellBuffer};
    Rectangle cells[(int)secretWord.length()];


    std::vector<std::string> hiddenWord;
    hiddenWord.emplace_back(" ");
    for (int i = 0; i < (int)secretWord.length() - 1; i++) {
        hiddenWord[0] += " ";
    }
    Text secretText[(int)secretWord.length()];
    int dim[2] = {1, (int)secretWord.length()};
    


    // Event Handling

    SDL_StartTextInput();
    while (running) {
        running = pollEvents(hiddenWord);

        keyboard(window, keys);

        writeTexts(secretText, hiddenWord, dim, WHITE);
        gridCreate(window, dimensions, letterColors,cells, true, secretText);
        displayMenu(cells, secretText, (int)secretWord.length(), *event);

        endingState(window);

        window.clear(backgroundColor);

        if (endState != "") {
            SDL_Delay(3000);
        }
    }
    SDL_StopTextInput();
    return;
}

bool Hangman::pollEvents(std::vector<std::string> &hiddenWord) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
        case SDL_TEXTINPUT:
            checkChar(*event->text.text, hiddenWord);
            break;
        case SDL_QUIT:
            return false;
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
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
    for (int i = 0; i < 26; i++) {
        if (keys[i].isClicked(*event)){
            checkChar(characters[i], hiddenWord);
        }
    }
    if (hiddenWord[0] == secretWord) {
        endState = "win"; 
        return false;
    }
    else if (currentTry >= maxAttempts) {
        endState = "lose";
        return false;
    }
    return true;
}

void Hangman::keyboard (Window &window, Rectangle keys[]) {
    SDL_Color WHITE = {255,255,255,255};

    // Set up the keyboard of buttons

    int dimensions[6] = {1,10, 2*window.getHeight() / 3, 105, 5, 7};

    std::vector<SDL_Color> keyBoardColor;
    SDL_Color KB = {0,0,0,255};
    for (int i = 0; i < 10; i++) {
        keyBoardColor.emplace_back(KB);
    }

    // Top Row
    Rectangle* kbTopRow = keys;  
    Text kbTopChar[10];  
    std::vector<std::string> topRow;
    topRow.emplace_back("qwertyuiop");

    writeTexts(kbTopChar, topRow, dimensions, WHITE);
    gridCreate(window, dimensions, keyBoardColor, kbTopRow, true, kbTopChar);

    // Middle Row
    Rectangle* kbMiddleRow = keys + 10;
    Text kbMiddleChar[9];
    std::vector<std::string> middleRow;
    middleRow.emplace_back("asdfghjkl");
    dimensions[1] = 9; // Number of Keys
    dimensions[2] = 2* window.getHeight() / 3 + 50; // Top buffer Position
    dimensions[3] = 55; // Padding
    writeTexts(kbMiddleChar, middleRow, dimensions, WHITE);
    gridCreate(window, dimensions, keyBoardColor, kbMiddleRow, true, kbMiddleChar);

    // Bottom Row
    Rectangle* kbBottomRow = keys + 19;
    Text kbBottomChar[7];
    std::vector<std::string> bottomRow;
    bottomRow.emplace_back("zxcvbnm");
    dimensions[1] = 7; // Number of keys
    dimensions[2] = 2* window.getHeight() / 3 + 100; //
    dimensions[3] = 5; 
    dimensions[4] = 55;
    writeTexts(kbBottomChar, bottomRow, dimensions, WHITE);
    gridCreate(window, dimensions, keyBoardColor, kbBottomRow, true, kbBottomChar);


    displayMenu(kbTopRow, kbTopChar, topRow[0].size(), *event);
    displayMenu(kbMiddleRow, kbMiddleChar, middleRow[0].size(), *event);
    displayMenu(kbBottomRow, kbBottomChar, bottomRow[0].size(), *event);
}

void Hangman::checkChar(char chosenChar, std::vector<std::string> &hiddenWord) {
    std::string preChange = hiddenWord[0];
    for (int i = 0; i < (int)secretWord.length(); i++) {
        if (chosenChar == secretWord[i]) {hiddenWord[0][i] = chosenChar;}
    }
    if (hiddenWord[0] == preChange) {currentTry++;}
}

void Hangman::endingState(Window &window) {
    if (running) {
        return;
    }
    if (endState == "") {
        return;
    }
    if (endState == "win") {
        highScore = (maxAttempts - currentTry)*100;
        winScreen(window, "Score: " + std::to_string(highScore));
        SDL_StopTextInput();
        return;
    }
    loseScreen(window, "Secret Word: " + secretWord);
    SDL_StopTextInput();
    return;
}