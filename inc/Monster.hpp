#ifndef MONSTER_H
#define MONSTER_H
#include <string>

using namespace std;

class Monster {
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
