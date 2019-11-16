#ifndef AVION_H
#define AVION_H
#include "Seat.hpp"
#include <string>
#include <vector>

using namespace std;

class Avion {
private:
  string planeName;
  vector <Seat*> seats;
  static int numberPlanes;

public:
    // Parameterized Constructor
    Avion(string planeName);
    void planeDetails();
    string getAvionName();
    vector<Seat> getSeats();
    void updateSeats(vector<Seat> s);
    ~Avion();
    static int getNumberPlanes(){return numberPlanes;};
};


#endif
