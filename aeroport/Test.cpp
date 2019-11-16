#include "Aeroport.hpp"
#include "Avion.hpp"
#include "Seat.hpp"
#include "Person.hpp"
#include <iostream>

using namespace std;

int main() {
  Person persona("Julian", "Lechuga");
  Person persona1("Mariana", "Avila");
  Aeroport airport1("AICM");

  Avion avion1("Starkiller");
  Avion avion2("Skywalker");
  avion1.planeDetails();
  avion2.planeDetails();
  persona.reserveSeat(avion1);
  persona1.reserveSeat(avion1);
  persona.reserveSeat(avion1);
  persona1.reserveSeat(avion1);
  persona.reserveSeat(avion1);
  persona1.reserveSeat(avion1);
  avion1.planeDetails();

  // airport1.landing(avion1);
  // airport1.showPlanes();
  std::cout << "Number of planes created: "<< Avion::getNumberPlanes()<<endl;
  std::cout << "Number of seats created: "<< Seat::getNumberSeatsCreated();
  return 0;
}
