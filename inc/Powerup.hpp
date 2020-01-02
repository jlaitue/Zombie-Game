#ifndef POWERUP_H
#define POWERUP_H
#include <string>
#include "Element.hpp"

using namespace std;

class Powerup: public Element{
public:
    // Parameterized Constructor
    Powerup(int id, int x, int y, string t = "static",  string s = "*");
    ~Powerup();
};

#endif
