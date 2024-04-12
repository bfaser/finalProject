#include <iostream>
#include <string>
#include "..\headers\graphics.hpp"

int main () {
  std::string placeHolder = "     ";
  std::string fiveLetter[5] = {placeHolder, placeHolder, placeHolder, placeHolder, placeHolder};

  // showGraphics();
  showWordle(fiveLetter);
}
