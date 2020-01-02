#ifndef DIAMOND_H
#define DIAMOND_H
#include <string>
#include "Element.hpp"

using namespace std;

class Diamond: public Element{
public:
    // Parameterized Constructor
    Diamond(int id, int x, int y, string t = "static",  string s = "$");
    ~Diamond();
};

#endif
