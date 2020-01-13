#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "Board.hpp"
#include "Player.hpp"

class Game {
private:
  int identifier;
  int gameLevel;
  int gameType;
  int totalDiamonds;
  vector <Board> boards;
  Player player;

public:
  static int gameCount;

    // Parameterized Constructor
    Game();

    void displayGame();
    void loadBoards();
    void loadUserBoards();
    void addBoard(int level, string filename);
    void getPlayerInfo();
    void run();

    ~Game();
};

#endif
