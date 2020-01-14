#ifndef MONSTER_H
#define MONSTER_H
#include <string>

using namespace std;

class Monster {
private:
  int xcoord;
  int ycoord;
  char symbol;

public:;
    //Default Constructor
    Monster();
    // Parameterized Constructor
    Monster(int id, int x, int y, string t, char s);

    // void showMonster();
    void updateMonsterCoords(int newRow, int newCol);
    int getMonsterY();
    int getMonsterX();
    char getSymbol();

    ~Monster();
};

#endif
