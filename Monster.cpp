#include "Monster.hpp"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(string nameValue){
  name = nameValue;
  cout<<"Monster created"<<endl;
}

void Monster::showMonster(){
  std::cout<<getMonsterName()<<std::endl;
}

string Monster::getMonsterName(){
  return name;
}

Monster::~Monster(){
  cout<<"Monster destroyed"<<endl;
}
