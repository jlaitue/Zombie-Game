#ifndef GAME_H
#define GAME_H
#include <string>
#include "Board.hpp"
using namespace std;

class Game {
private:
  int level;
  int identifier;
  Board board;

public:
  static int gameCount;

    // Parameterized Constructor
    Game(int identifier);

    void displayGame();
    void positionObjects(int nDiam, int nMons, int nDoors, int nStars, int nWalls);
    void readGame(string filename);
    void createTheMatrix(int level, string filename);
    void getGameLevel();
    ~Game();
};

#endif
