#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "Board.hpp"
#include "Player.hpp"
using namespace std;

class Game {
private:
  int level;
  int identifier;
  // vector <Board> boards;
  Board boards[5];
  Player player;

public:
  static int gameCount;

    // Parameterized Constructor
    Game();

    void displayGame();
    void loadBoards();
    void addBoard(int level, string filename, string directive);
    void run();

    ~Game();
};

#endif
