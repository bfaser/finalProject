#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <string>
#include <vector>

class Wordle {
private:
    int highscore;
    std::string secretWord;
    int tries;
    std::vector<std::string> validWords;

    void initWordsVec ();
    bool submit ();
public:
    Wordle();

    int play();
};

#endif