#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "Seat.hpp"
#include "Avion.hpp"
using namespace std;

class Person {
private:
  string name;
  string lastName;
  // Seat seat;

public:
    // Parameterized Constructor
    Person(string name, string lastName);

    void printPerson();
    string getPersonName();
    int reserveSeat(Avion& plane);
    ~Person();
};

#endif
