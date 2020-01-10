#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Player: public Element{
private:
  int nDiamonds;
  int nPowers;
  int nLives;
public:
  static int playerCount;
    // Parameterized Constructor
    Player();
    Player(int id, int x, int y, string t = "player");
    int numDiamonds();
    int numPowerups();
    int numLives();
    void incrementDiamonds();
    void incrementPowerups();
    void decrementPowerups();
    void decrementLives();
    void movement();
    ~Player();
};

#endif
