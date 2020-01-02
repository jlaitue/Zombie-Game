#include "../inc/Door.hpp"
#include <iostream>
#include <string>

using namespace std;

Door::Door(int id, int x, int y, string t, string s):
Element(id,x,y,t,s)
{
  cout<<"Door "<<id<<"created"<<endl;
}

Door::~Door(){
  cout<<"Door destroyed"<<endl;
}
