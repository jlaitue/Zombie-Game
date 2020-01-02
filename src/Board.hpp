#ifndef BOARD_H
#define BOARD_H
#include <string>
const size_t rows = 20;
const size_t columns = 40;
using namespace std;

class Board {
private:
  int level = 3;
  int identifier;
  size_t n = rows;
  size_t m = columns;

  string matrix[rows][columns];

public:
    // Parameterized Constructor
    Board(int identifier, string directive);

    void displayBoard();
    void positionObjects(int nDiam, int nMons, int nDoors, int nStars, int nWalls);
    void readBoard(string filename);
    void createTheMatrix(string filename);
    ~Board();
};

#endif
