#include "../inc/Monster.hpp"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(int id, string t, int x, int y, string s):
Element(id,t,x,y,s)
{
  cout<<"Monster "<<id<<"created"<<endl;
}

Monster::~Monster(){
  cout<<"Monster destroyed"<<endl;
}
