#include "../inc/Player.hpp"
#include <iostream>
#include <string>

using namespace std;

Player::Player(int id, int x, int y, string t, string s):
Element(id,x,y,t,s)
{
  cout<<"Player "<<id<<"created"<<endl;
}

Player::~Player(){
  cout<<"Player destroyed"<<endl;
}
