#include "../inc/Player.hpp"
#include <iostream>
#include <string>

using namespace std;

int Player::playerCount = 0;

Player::Player(){

}

Player::Player(int id, int x, int y, string t):
Element(id,x,y,t,'O'),nDiamonds(0), nPower(0),nLives(3)
{
  playerCount++;
  cout<<"Player created"<<endl;
}

Player::~Player(){
  cout<<"Player destroyed"<<endl;
}
