#ifndef GAME_HPP
#define GAME_HPP

#include "../SDL2/include/SDL2/SDL.h"
#include "../headers/SDL2/window.hpp"

class Game {
    protected:
    SDL_Color backgroundColor;
    int highScore;
    int maxAttempts;

    public: 
    Game();
};

#endif