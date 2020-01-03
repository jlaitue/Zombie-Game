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
  static int objectCount;
  static int deletedCount;
    //Default Constructor
    Element();
    // Parameterized Constructor
    Element(int id, int x, int y, string t, string s);

    void showElement();
    void updateSymbol(string newS);
    void updateElement(int x, int y, string t, string s);
    string getSymbol();

    ~Element();
};

#endif
