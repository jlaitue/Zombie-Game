#include "../inc/Element.hpp"
#include <iostream>
#include <string>

using namespace std;

Element::Element(int id, string t, int x, int y, string s):
idtag(id), type(t), xcoord(x), ycoord(y),symbol(s)
{
  cout<<"Element created"<<endl;
}

void Element::showElement(){
  cout<<"Id  : "<<idtag<<endl;
  cout<<"Type: "<<type<<endl;
  cout<<"X   : "<<xcoord<<endl;
  cout<<"Y   : "<<ycoord<<endl;
  cout<<"Symb: "<<symbol<<endl;
}

string Element::getSymbol(){
  return symbol;
}

Element::~Element(){
  cout<<"Element destroyed"<<endl;
}
