#ifndef AEROPORT_H
#define AEROPORT_H
#include <string>
#include <vector>
#include "Avion.hpp"
using namespace std;

class Aeroport {
private:
  string name;
  vector <Avion> planes{};

public:
    // Parameterized Constructor
    Aeroport(string nameValue);

    void printAeroport();
    void landing(Avion& a);
    string getAeroportName();
    void showPlanes();
    ~Aeroport();
};

#endif
