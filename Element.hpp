#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

using namespace std;

class Element {
private:
  string type;
  int xcoord;
  int ycoord;
  string symbol;

public:
    // Parameterized Constructor
    Element(string type, int x, int y, string symbol);

    void showElement();
    string getElementType();

    ~Element();
};

#endif
