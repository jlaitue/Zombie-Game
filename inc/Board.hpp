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
  int rowOrigin;
  int colOrigin;
  int infoBoxIdent;
  int availableDiamonds;
  int availableMonsters;
  int availablePowerups;
  int availableDoors;
  int availableWalls;
  Element matrix[rows][columns];

public:
  static int boardCount;

    // Parameterized Constructor
    Board();
    Board(int identifier);

    void displayBoard();
    void positionObjects();
    void readBoard(int level, string filename);
    void createTheMatrix(int level, string filename);
    bool openDoor();
    void validateMovement(int &rowPosition, int &colPosition, char nextStr,
      bool &movementValid, bool &nextBoard, Player &player, int moveCase);

    string getBoardName();
    int getNumberDiamonds();
    //
    // void updateNumberDiamonds(int newValue);
    // void updateNumberMonsters(int newValue);
    // void updateNumberDoors(int newValue);
    // void updateNumberPowerups(int newValue);
    // void updateNumberWalls(int newValue);

    void moveMonsters(int emptyRows, int emptyCols);
    void clearMonsters();

    string play(Player &player);
    void creator();
    ~Board();
};

#endif
