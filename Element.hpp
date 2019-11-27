#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

using namespace std;

class Element {
private:
  string name;

public:
    // Parameterized Constructor
    Element(string name);

    void showElement();
    // void setMonAttribut(int value);
    string getElementName();
    ~Element();
};

#endif
