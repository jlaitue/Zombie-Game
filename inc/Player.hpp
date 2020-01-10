#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Player: public Element{
private:
  int nDiamonds;
  int nPower;
  int nLives;
public:
  static int playerCount;
    // Parameterized Constructor
    Player();
    Player(int id, int x, int y, string t = "player");
    void movement();
    ~Player();
};

#endif
