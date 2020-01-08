#include "../inc/Monster.hpp"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(int id, int x, int y, string t, char s):
Element(id,x,y,t,s)
{
  cout<<"Monster "<<id<<"created"<<endl;
}

Monster::~Monster(){
  cout<<"Monster destroyed"<<endl;
}
