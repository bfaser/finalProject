# Computer Science 172 - Whitworth University
Author: Brodin Faser, Sam Vaughn

Date: Spring, 2024 

## Table of Contents

- [Computer Science 172 - Whitworth University](#computer-science-172---whitworth-university)
  - [Table of Contents](#table-of-contents)
  - [Structure and Overview](#structure-and-overview)
  - [Main Menu](#main-menu)
  - [Games](#games)
    - [Wordle](#wordle)
    - [Connections](#connections)
    - [Hangman](#hangman)
    - [Snake](#snake)
    - [Minesweeper](#minesweeper)
    - [Sudoku](#sudoku)
  - [Other Core Features](#other-core-features)
    - [User System](#user-system)
  - [Acknowledgments](#acknowledgments)

## Structure and Overview

<!-- 
C++ project with underlying SDL2 Framework. 
Emphasis on object oriented programming and code readability. 

-->

## Main Menu

## Games
The games that this project will aim to include are based off the New York Times games. 
These games include Wordle, Connections, Hangman, and possibly a cross word.

Possible games: Snake, minesweeper, sudoku, asteroids.

### Wordle
In this recreation of wordle, the computations will be done in a wordle class, called through an initialization function in main. 
For rendering, a window will be opened from the main menu window that will display the typed word onto the screen. 

Submission of the guessed 5-letter word will be submitted using the enter key.
This will be checked against a text document of valid 5-letter words. If the word is found to be a valid word, it will be compared against the target, secret word.
For every incorrect letter, the cell containing that letter will turn $\textcolor{red}{red}$.
For every correct letter in the incorrect place, the cell containing that letter will turn $\textcolor{orange}{orange}$.
For every correct letter in the correct place, the cell containing that letter will turn $\textcolor{green}{green}$. 
Once all the cells are $\textcolor{green}{green}$, the game is over and won. 
If the user goes through **5** iterations of this process without guessing the target word, the user loses the game.

<!-- ### Connections
Connections is another New York Times mini-game, similar to Wordle.
Connections has a 4x4 grid of cells that each have a word in them.
The Goal of Connections is to find 4 cells that have a something in common, determined behind the scenes at the beginning of the game. 
When the user selects four cells they believe to have a commonality, they are able to submit this via the *Enter* button.
However, a user only gets to check and submit **4** incorrect guesses before losing the game
(A submission of 4 cells with a common trait does *not* count towards this).
If the user submits 4 cells with common traits, those cells migrate to the 1st available row, merge together, and display the secret common trait.
If the user is unable to find all the hidden traits within the alloted guesses, the traits are shown and the user loses the game. -->

------ 25 Apr --------
Small error with repeated letters persists 


### Hangman
Hangman is one of the most popular and well-known word-guessing games.
A simple explanation of how to play is to guess the hidden word letter-by-letter with less than **5** incorrect guesses.
Before any guesses, there will be blank spaces corresponding to the number of letters in the hidden word.
After each guess, the submitted letter will be checked against the hidden word.
If the letter is within that word, the space corresponding to that letter will be filled in with the guessed letter. 
Every occurrence of that letter will be filled in.
If the letter is not found within the word, one of the **5** incorrect guesses will be used and a graphical representation of this will be drawn. 
Since this is a school project, it seems inappropriate to draw a hangman as the graphical representation.
$\textcolor{red}{SUBSTITUTE\ GRAPHIC}$.
The user wins the game if the hidden word is guessed before running out of incorrect guesses. 
If the user is not able to guess the hidden word before running out of guesses, the user loses.

<!-- ### Crossword -->
  
### Snake 

### Minesweeper

### Sudoku 

## Other Core Features

Aside from the games, there are a few other core features that this program intends to implement. 

### User System

This program will use a sign-in system, where new users are able to create a username and password, then log-in later as a pre-existing user with the same login credentials.
This will be done through the use of a user text file. 

## Acknowledgments

For the wordle valid words list, we used Github user dracos' public repository of valid words. The link to ths repository can be found here: https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93.

For the common words list, we used Github user shmookey's public repository. The link to this repository can be found here: https://gist.github.com/shmookey/b28e342e1b1756c4700f42f17102c2ff#file-words.

For the hangman words list, we used Github user Tom25's word list from their public repository. The link to this repository can be found here: https://github.com/Tom25/Hangman/blob/master/wordlist.txt.