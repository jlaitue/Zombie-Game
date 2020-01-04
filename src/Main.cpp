#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include "../inc/Board.hpp"
#include "../inc/Game.hpp"
using namespace std;

int main() {
  Game game;
  game.loadBoards();
  game.run();

  return 0;
}
