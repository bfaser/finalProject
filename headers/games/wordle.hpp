#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <string>
#include <vector>

#include "../headers/games/game.hpp"
#include "../headers/SDL2/window.hpp"
#include "../SDL2/include/SDL2/SDL.h"

class Wordle : public Game  {
private:
    std::string secretWord;
    int currentTry;
    std::vector<std::string> validWords;
    bool running;
    std::vector<SDL_Color> color;
    std::vector<std::string> guessedWords;
    
    bool submit (std::string &enteredWord);
    bool pollEvents ();
    void initWordsVec ();
public:
    Wordle();


    void play (Window &window);
};

#endif