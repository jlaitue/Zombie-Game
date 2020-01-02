#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Player: public Element{
public:
    // Parameterized Constructor
    Player(int id, int x, int y, string t = "dynamic", string s = "J");
    ~Player();
};

#endif
