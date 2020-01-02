#include "../inc/Diamond.hpp"
#include <iostream>
#include <string>

using namespace std;

Diamond::Diamond(int id, int x, int y, string t, string s):
Element(id,x,y,t,s)
{
  cout<<"Diamond "<<id<<"created"<<endl;
}

Diamond::~Diamond(){
  cout<<"Diamond destroyed"<<endl;
}
