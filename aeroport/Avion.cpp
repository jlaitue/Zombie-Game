#include "Avion.hpp"
#include "Seat.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Avion::numberPlanes = 0;

// vector <Seat>  createSeats(){
//   vector <Seat> seatsVector;
//   for (int i = 1; i < 6; i++) {
//     Seat seat(i);
//     seatsVector.push_back(seat);
//   }
//   return seatsVector;
// }

Avion::Avion(string name){
  // string x = to_string(numberPlanes);
  planeName = name;
  for (int i = 1; i < 6; i++) {
    Seat *seat = new Seat(i);
    seats.push_back(seat);
  }
  // seats = createSeats();
  Avion::numberPlanes++;
  cout<<"\nCreation of plane "<<getAvionName()<<endl;
}

Avion::~Avion(){
  cout<<"\nDestruction of airplane "<<getAvionName()<<endl;
}

void Avion::planeDetails(){
  cout<<"Avion: "<<getAvionName()<<endl;
  vector<Seat>::iterator element;
    for (element = seats.begin(); element != seats.end(); ++element) {
      cout <<"Asiento: "<< element->getSeat()<<"  "<<"Disponible: "
      << element->seatAvailability()<<" "<<element->getUserName()<<endl;
    }
  cout<<"\n"<<endl;
}

string Avion::getAvionName(){
  return planeName;
}

vector<Seat> Avion::getSeats(){
  return seats;
}

void Avion::updateSeats(vector<Seat> seatsV){
  seats = seatsV;
}
