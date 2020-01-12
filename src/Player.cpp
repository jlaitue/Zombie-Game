#include "../inc/Player.hpp"
#include <iostream>
#include <string>

using namespace std;

int Player::playerCount = 0;

Player::Player(){
string defaultPlayers[] = {"Iron Man", "SpiderMan", "Thor", "Wolverine", "Phoenix"};
nDiamonds = 0;
nPowers = 0;
nLives = 3;
name = defaultPlayers[rand() % 5];
// cout<<"Player created"<<endl;
}

// Player::Player(int id, int x, int y, string t):
// Element(id,x,y,t,'O'),nDiamonds(30), nPowers(30),nLives(30)
// {
//   playerCount++;
//   cout<<"Player created"<<endl;
// }
string Player::getName(){
  return name;
}

string Player::updateName(string newName){
  if (newName != "") {
    name = newName;
  }
  return name;
}

int Player::Diamonds(){
  return nDiamonds;
}

int Player::Powerups(){
  return nPowers;
}

int Player::Lives(){
  return nLives;
}

void Player::incrementDiamonds(){
  nDiamonds++;
}

void Player::incrementPowerups(){
  nPowers++;
}

void Player::incrementLives(){
  nLives++;
}

void Player::decrementDiamonds(){
  nDiamonds--;
}

void Player::decrementPowerups(){
  nPowers--;
}

void Player::decrementLives(){
  nLives--;
}


Player::~Player(){
  // cout<<"Player destroyed"<<endl;
}
