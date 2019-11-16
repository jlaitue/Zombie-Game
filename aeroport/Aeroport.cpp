#include "Aeroport.hpp"
#include "Avion.hpp"
#include <iostream>
#include <string>

using namespace std;

Aeroport::Aeroport(string nameValue){
  name = nameValue;
  cout<<"\nCreation of airport "<<getAeroportName()<<endl;
}

Aeroport::~Aeroport(){
  cout<<"\nDestruction of airport "<<getAeroportName();
}

void Aeroport::printAeroport(){
  cout<<getAeroportName()<<endl;
}

string Aeroport::getAeroportName(){
  return name;
}

void Aeroport::landing(Avion& a){
  planes.push_back(a);
}

void Aeroport::showPlanes(){
  cout<<"Planes parked in airport "<<getAeroportName()<<endl;
  vector<Avion>::iterator element;
    for (element = planes.begin(); element != planes.end(); ++element) {
        cout <<"Avion: "<< element->getAvionName()<<endl;
    }
}
