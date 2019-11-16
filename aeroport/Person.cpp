#include "Person.hpp"
#include "Avion.hpp"
#include "Seat.hpp"
#include <iostream>
#include <string>

using namespace std;

Person::Person(string n, string lN):name(n),lastName(lN){
  cout<<"\nCreation of person "<<getPersonName()<<endl;
}

Person::~Person(){
  cout<<"\nDestruction of person "<<getPersonName();
}

void Person::printPerson(){
  cout<<getPersonName()<<endl;
}

string Person::getPersonName(){
  return name;
}

int Person::reserveSeat(Avion& plane){
  vector <Seat> planeSeats = plane.getSeats();
  vector<Seat>::iterator element;
    for (element = planeSeats.begin(); element != planeSeats.end(); ++element) {
      if (element->seatAvailability()) {
        cout<<"\n "<<getPersonName()<<" reservo el asiento: "<<" "<<
        element->getSeat()<<endl;
        element->changeStatus(getPersonName());
        plane.updateSeats(planeSeats);
        return 0;
      }
    }
    cout<<"\nLo sentimos. No existe disponibilidad de asientos en el avion."<<endl;
    return 0;
}
