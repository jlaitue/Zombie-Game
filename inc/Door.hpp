#ifndef DOOR_H
#define DOOR_H
#include <string>
#include "Element.hpp"

using namespace std;

class Door: public Element{
public:
    // Parameterized Constructor
    Door(int id, int x, int y, string t = "static",  char s = '/');
    ~Door();
};

#endif
