#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include "Element.hpp"

using namespace std;

class Monster: public Element{
public:
    // Parameterized Constructor
    Monster(int id, string t = "dynamic", int x = 0, int y = 0, string s="M");
    ~Monster();
};

#endif
