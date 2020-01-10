#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "Element.hpp"
#include "Player.hpp"
using namespace std;

const int rows = 20;
const int columns = 40;

class Board {
private:
  int level;
  int identifier;
  string boardName;
  int n = rows;
  int m = columns;
  Element matrix[rows][columns];

public:
  static int boardCount;

    // Parameterized Constructor
    Board();
    Board(int identifier);

    void displayBoard();
    void positionObjects(int nDiam, int nMons, int nDoors, int nStars, int nWalls);
    void readBoard(string filename);
    void createTheMatrix(int level, string filename);
    bool openDoor();
    void validateMovement(int &rowPosition, int &colPosition, char nextStr,
      bool &movementValid, bool &nextBoard, Player &player, int moveCase);
    string getBoardName();
    string play(Player &player);
    void moveMonsters(int emptyRows, int emptyCols);
    ~Board();
};

#endif
