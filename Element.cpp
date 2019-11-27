#include "Element.hpp"
#include <iostream>
#include <string>

using namespace std;

Element::Element(string nameValue){
  name = nameValue;
  cout<<"Element destroyed"<<endl;
}

void Element::showElement(){
  std::cout<<getElementName()<<std::endl;
}

string Element::getElementName(){
  return name;
}

Element::~Element(){
  cout<<"Element destroyed"<<endl;
}
