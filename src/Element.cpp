#include "Element.hpp"
#include <iostream>
#include <string>

using namespace std;

Element::Element(string typeValue, int xValue, int yValue, string symbolValue){
  type = typeValue;
  xcoord = xValue;
  ycoord = yValue;
  symbol = symbolValue;
  cout<<"Element created"<<endl;
}

void Element::showElement(){
  cout<<type<<endl;
  cout<<xcoord<<endl;
  cout<<ycoord<<endl;
  cout<<symbol<<endl;
}

string Element::getElementType(){
  return type;
}

Element::~Element(){
  cout<<"Element destroyed"<<endl;
}
