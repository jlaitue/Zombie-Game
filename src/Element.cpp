#include "../inc/Element.hpp"
#include <iostream>
#include <string>

using namespace std;

int Element::objectCount = 0;

Element::Element(){
  objectCount++;
  idtag = objectCount;
  symbol = " ";
  cout<<"Element "<<type<<" "<<idtag<<" created"<<endl;
}

Element::Element(int id, int x, int y, string t, string s):
idtag(id), xcoord(x), ycoord(y),type(t),symbol(s)
{
  cout<<"Element "<<type<<" "<<idtag<<" created"<<endl;
  objectCount++;
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

void Element::updateElement(int x, int y, string t, string s){
  xcoord = x;
  ycoord = y;
  type = t;
  symbol = s;
}

int Element::deletedCount = objectCount;

Element::~Element(){
  deletedCount--;
  cout<<"Element "<<type<<" "<<idtag<<" destroyed"<<endl;
}
