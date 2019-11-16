#ifndef SEAT_H
#define SEAT_H
#include <string>
// #include "Person.hpp"
using namespace std;
class Seat {
private:
  int seat_id;
  bool available = true;
  string userName = "";
  static int numberSeatsCreated;
public:
    // Parameterized Constructor
    Seat(int seat_number);
    int getSeat();
    bool seatAvailability();
    void changeStatus(string personsName);
    string getUserName();
    ~Seat();
    static int getNumberSeatsCreated(){return numberSeatsCreated;}
};

#endif
