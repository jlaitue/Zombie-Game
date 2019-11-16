#include "Seat.hpp"
#include <iostream>
#include <string>

using namespace std;
int Seat::numberSeatsCreated = 0;
Seat::Seat(int seat_number): seat_id(seat_number){
  numberSeatsCreated++;
  std::cout<<"\nCreation of seat "<<getSeat()<<endl;
}

Seat::~Seat(){
  std::cout<<"\nDestruction of seat "<<getSeat()<<endl;
}

int Seat::getSeat(){
  return seat_id;
}

bool Seat::seatAvailability(){
  return available;
}

void Seat::changeStatus(string personsName){
  this->userName = personsName;
  this->available = false;
}

string Seat::getUserName(){
  return userName;
}
