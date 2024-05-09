#ifndef HANGMAN_HPP
#define HANGMAN_HPP

#include <vector>
#include "../headers/games/game.hpp"
#include "../headers/SDL2/window.hpp"
#include "../headers/SDL2/rectangle.hpp"

class Hangman : public Game {
private:
    std::vector<SDL_Color> letterColors;
    std::string secretWord;
    Rectangle keys[26];
    static std::string characters;
    Rectangle* livesGraphic;
    int currentTry;

    bool initialize ();
    bool pollEvents (std::vector<std::string> &hiddenWord);
    void keyboard (Window &window, Rectangle keys[]);
    void checkChar(char chosenChar, std::vector<std::string> &hiddenWord);
    void endingState(Window &window);
public:
    Hangman();
    ~Hangman();

    void play(Window &window);
};

#endif