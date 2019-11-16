#include "Boxint.hpp"
#include <iostream>

Boxint::Boxint(int value){
  x = value;
}

void Boxint::printBox(){
  std::cout<<getBox()<<std::endl;
}

int Boxint::getBox(){
  return x;
}

void Boxint::setMonAttribut(int value){
  x = value;
}
