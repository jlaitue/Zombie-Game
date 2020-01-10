#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Player{
private:
  int nDiamonds;
  int nPowers;
  int nLives;

public:
  static int playerCount;
    // Parameterized Constructor
    Player();
    // Player(int id, int x, int y, string t = "player");
    int Diamonds();
    int Powerups();
    int Lives();

    void incrementDiamonds();
    void incrementPowerups();
    void decrementPowerups();
    void decrementLives();

    ~Player();
};

#endif
