#ifndef GAME_H
#define GAME_H
#include <string>
#include "Board.hpp"
using namespace std;

class Game {
private:
  int level;
  int identifier;
  // Will transform into a data array for holding several boards
  Board board;

public:
  static int gameCount;

    // Parameterized Constructor
    Game(int identifier);

    void displayGame();
    void getGameLevel();
    void addBoard(int level, string filename, string directive);
    void executeGame();
    ~Game();
};

#endif
