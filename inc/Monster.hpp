#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Monster: public Element{
public:
    // Parameterized Constructor
    Monster(int id, int x = 0, int y = 0, string t = "dynamic", char s = 'M');
    ~Monster();
};

#endif
