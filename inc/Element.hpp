#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

using namespace std;

class Element {
private:
  int idtag;
  int xcoord;
  int ycoord;
  string type;
  string symbol;

public:
    // Parameterized Constructor
    Element(int id, int x, int y, string t, string s);

    void showElement();
    string getSymbol();

    ~Element();
};

#endif
