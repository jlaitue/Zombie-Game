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
  char symbol;

public:
  static int objectCount;
  static int deletedCount;
    //Default Constructor
    Element();
    // Parameterized Constructor
    Element(int id, int x, int y, string t, char s);

    void showElement();
    void updateSymbol(char newS);
    void updateElement(int x, int y, string t, char s);
    char getSymbol();

    ~Element();
};

#endif
