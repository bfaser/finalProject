#include "../headers/SDL2/rectangle.hpp"
#include "../headers/SDL2/text.hpp"
#include "../headers/games/game.hpp"

Game::Game() {
    running = false;
    highScore = 0;
    endState = "";
    maxAttempts = 5; // Generic Max Attempts
    backgroundColor = {100,100,100,255}; // Default Grey Background
}

void Game::winScreen(Window &window, std::string supplementaryText) {
    int position[2] = {window.getWidth() / 2, window.getHeight() /2};
    SDL_Color winBackground = {255, 255, 255, 190};
    SDL_Color textColor = {123, 182, 97,255};
    Rectangle winRect(window.getWidth(), window.getHeight(), position, winBackground);
    Text winText(Window::renderer, 60, "YOU WON", textColor);
    Text supText(Window::renderer, 60, supplementaryText, {0,0,0,255});

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);
    winRect.draw();
    winText.display(window.getWidth() / 2, (window.getHeight() / 2) - 40, Window::renderer);
    supText.display(window.getWidth() / 2, (window.getHeight() / 2) + 40, Window::renderer);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_NONE);

    winRect.~Rectangle();
    winText.~Text();
    return;
}

void Game::loseScreen(Window &window, std::string supplementaryText) {
    int position[2] = {window.getWidth() / 2, window.getHeight() /2};
    SDL_Color loseBackground = {0, 0, 0, 190};
    SDL_Color textColor = {202, 52, 51, 255};
    Rectangle loseRect(window.getWidth(), window.getHeight(), position, loseBackground);
    Text loseText(Window::renderer, 60, "YOU LOST", textColor);
    Text supText(Window::renderer, 60, supplementaryText, {255, 255, 255, 255});

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_BLEND);

    loseRect.draw();
    loseText.display(window.getWidth() / 2, (window.getHeight() / 2) - 40, Window::renderer);
    supText.display(window.getWidth() / 2, (window.getHeight() / 2) + 40, Window::renderer);

    SDL_SetRenderDrawBlendMode(Window::renderer, SDL_BLENDMODE_NONE);

    loseRect.~Rectangle();
    loseText.~Text();
    return;
}