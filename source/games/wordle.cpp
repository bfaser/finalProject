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

Wordle::Wordle() {
    highscore = 0;
    if (validWords.size() == 0) {
        initWordsVec();
    }
    for (int i = 0; i < 25; i++) {
        color[i] = {140,140,140,255};
    }

    std::cout << secretWord;
}

std::vector<std::string> Wordle::getWordsVec() const {
    return validWords;
}


std::string Wordle::getSecretWord() const {
    return secretWord;
}