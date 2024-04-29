#include "../headers/SDL2/rectangle.hpp"
#include "../headers/SDL2/text.hpp"
#include "../headers/games/game.hpp"

Game::Game() {
    highScore = 0;
    endState = "";
    maxAttempts = 5; // Generic Max Attempts
    backgroundColor = {100,100,100,255}; // Default Grey Background
}

void Game::winScreen(Window &window) {
    int position[2] = {window.getWidth() / 2, window.getHeight() /2};
    SDL_Color winBackground = {255, 255, 255, 100};
    SDL_Color textColor = {80,200,120,255};
    Rectangle winRect(window.getWidth(), window.getHeight(), position, winBackground);
    Text winText(Window::renderer, 60, "YOU WON", textColor);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
    winRect.draw();
    winText.display(window.getWidth() / 2, window.getHeight() / 2, Window::renderer);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_NONE);

    winRect.~Rectangle();
    winText.~Text();
    return;
}

void Game::loseScreen(Window &window) {
    int position[2] = {window.getWidth() / 2, window.getHeight() /2};
    SDL_Color loseBackground = {0, 0, 0, 100};
    SDL_Color textColor = {255,40,0,255};
    Rectangle loseRect(window.getWidth(), window.getHeight(), position, loseBackground);
    Text loseText(Window::renderer, 60, "YOU LOST", textColor);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);

    loseRect.draw();
    loseText.display(window.getWidth() / 2, window.getHeight() / 2, Window::renderer);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_NONE);

    loseRect.~Rectangle();
    loseText.~Text();
    return;
}