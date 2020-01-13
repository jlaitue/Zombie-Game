#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include "Board.hpp"
#include "Player.hpp"

class Game {
private:
  int identifier;
  int gameBlock;
  int gameType;
  int gameStages;
  int totalDiamonds;
  bool virusMode;
  vector <string> userFileNames;
  vector <Board> boards;
  Player player;

public:
  static int gameCount;

    // Parameterized Constructor
    Game();

    void displayGame();
    void loadRandomBoards();
    void loadUserBoards();
    void addBoard(int level, string filename);
    void getPlayerInfo();
    void run();

    ~Game();
};

#endif
