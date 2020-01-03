#include "../inc/Player.hpp"
#include <iostream>
#include <string>

using namespace std;

Player::Player(int id, int x, int y, string t, string s):
Element(id,x,y,t,s),nDiamonds(0), nPower(0),nLives(3)
{
  cout<<"Player created"<<endl;
}

void Player::movement(){
}

Player::~Player(){
  cout<<"Player destroyed"<<endl;
}
