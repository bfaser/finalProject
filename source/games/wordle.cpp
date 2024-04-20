#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

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

Wordle::Wordle() {
    highscore = 0;
    if (validWords.size() == 0) {
        initWordsVec();
    }
    std::cout << validWords.size();
}

int Wordle::play() {
    // Open file

    // Choose a random word from word list and store it as secretWord

    // Close file

    // number of guesses reset to 0
    
    // Display Game and Play
}