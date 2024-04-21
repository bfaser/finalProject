#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <string>
#include <vector>

#include "../SDL2/include/SDL2/SDL.h"

class Wordle {
private:
    int highscore;
    std::string secretWord;
    int tries;
    std::vector<std::string> validWords;
    
    void initWordsVec ();
public:
    Wordle();

    std::vector<std::string> getWordsVec() const;
    std::string getSecretWord() const;
    SDL_Color color[25];
    std::string guessedWords[5];
};

#endif