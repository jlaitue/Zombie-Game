#include "../inc/Element.hpp"
#include <iostream>
#include <string>

using namespace std;

// int Element::objectCount = 1;

Element::Element(int id, int x, int y, string t, string s):
idtag(id), xcoord(x), ycoord(y),type(t),symbol(s)
{
  cout<<"Element "<<type<<" "<<idtag<<" created"<<endl;
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

void Element::updateSymbol(string newS){
  symbol = newS;
}

Element::~Element(){
  cout<<"Element destroyed"<<endl;
}
