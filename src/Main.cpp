#include "../inc/Game.hpp"
#include "../inc/Player.hpp"
#include <iostream>
using namespace std;

int main() {
  Game game;
  game.loadBoards();
  game.run();
  return 0;
}
