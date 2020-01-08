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
    // Parameterized Constructor
    Player(int id, int x, int y, string t = "player", char s = 'J');
    void movement();
    ~Player();
};

#endif
