#include "../inc/Powerup.hpp"
#include <iostream>
#include <string>

using namespace std;

Powerup::Powerup(int id, int x, int y, string t, string s):
Element(id,x,y,t,s)
{
  cout<<"Powerup "<<id<<"created"<<endl;
}

Powerup::~Powerup(){
  cout<<"Powerup destroyed"<<endl;
}
