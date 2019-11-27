#ifndef MONSTER_H
#define MONSTER_H
#include "Element.hpp"
#include <string>

using namespace std;

class Monster: public Element {
private:
  string name;

public:
    // Parameterized Constructor
    Monster(string name);

    void showMonster();
    // void setMonAttribut(int value);
    string getMonsterName();
    ~Monster();
};

#endif
