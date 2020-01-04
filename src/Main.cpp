#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
// #include "../inc/Element.hpp"
// #include "../inc/Monster.hpp"
// #include "../inc/Door.hpp"
#include "../inc/Board.hpp"
#include "../inc/Game.hpp"
using namespace std;

int main() {
  Game game1(1);
  game1.addBoard(3,"FIRE.txt","read");
  game1.runGame();
  return 0;
}
