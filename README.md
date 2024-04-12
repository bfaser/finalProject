# Final Project Read-Me

## Table of Contents

- [Structure](#structure)

## Structure

## Main Menu

## Games
The games that this project will aim to include are based off the New York Times games. 
These games include Wordle, Connections, Hangman, and possibly a cross word.

Possible games: Snake, minesweeper, sudoku, asteroids

### Wordle
In this recreation of wordle, the computations will be done in a wordle class, called through an initialization function in main. 
For rendering, a window will be opened from the main menu window that will display the typed word onto the screen. 

Submission of the guessed 5-letter word will be submitted using the enter key. This will be checked against a text document of valid 5-letter words. If the word is found to be a valid word, it will be compared against the target, secret word. For every correct letter in the incorrect place, the cell containing that letter will turn (incorrect place color). For every correct letter in the correct place, the cell containing that letter will turn (entirely correct color). Once all the cells are (entirely correct color), the game is over and won. If the user goes through (# of tries) iterations of this process without guessing the target word, the user loses the game.

### Connections

### Hangman

### Crossword

## Other Core Features

Aside from the games, there are a few other core features that this program intends to implement. 

### User System

This program will use a sign-in system, where new users are able to create a username and password, then log-in later as a pre-existing user with the same login credentials. This will be done through the use of a user text file. 