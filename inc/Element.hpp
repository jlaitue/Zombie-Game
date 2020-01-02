#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

using namespace std;

class Element {
private:
  int idtag;
  string type;
  int xcoord;
  int ycoord;
  string symbol;

public:
    // Parameterized Constructor
    Element(int id, string t, int x, int y, string s);

    void showElement();
    string getSymbol();

    ~Element();
};

#endif
