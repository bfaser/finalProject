#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "../SDL2/include/SDL2/SDL.h"
#include "../headers/SDL2/window.hpp"

class Game {
    protected:
    SDL_Color backgroundColor;
    int highScore;
    int maxAttempts;
    std::string endState; // "" represents not the end, "win" represents win state, "lose" represents lose state
    
    void winScreen(Window &window, std::string supplementaryText);
    void loseScreen(Window &window, std::string supplementaryText);

    public: 
    Game();
};

#endif