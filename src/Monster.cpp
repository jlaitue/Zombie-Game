#include "../inc/Monster.hpp"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(){
  xcoord = 0;
  ycoord = 0;
  symbol = 'M';
  // cout<<"Monster "<<type<<" "<<idtag<<" created"<<endl;
}

Monster::Monster(int id, int x, int y, string t, char s): xcoord(x), ycoord(y),symbol(s)
{
  // cout<<"Monster "<<type<<" "<<idtag<<" created"<<endl;
}

// void Monster::showMonster(){
//   cout<<"Id  : "<<idtag<<endl;
//   cout<<"Type: "<<type<<endl;
//   cout<<"X   : "<<xcoord<<endl;
//   cout<<"Y   : "<<ycoord<<endl;
//   cout<<"Symb: "<<symbol<<endl;
// }

char Monster::getSymbol(){
  return symbol;
}

int Monster::getMonsterX(){
  return xcoord;
}

int Monster::getMonsterY(){
  return ycoord;
}

void Monster::updateMonsterCoords(int newRow, int newCol){
  xcoord = newRow;
  ycoord = newCol;
}

Monster::~Monster(){
  // cout<<"Monster "<<type<<" "<<idtag<<" destroyed"<<endl;
}
