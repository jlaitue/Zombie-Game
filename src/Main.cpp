#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
// #include "../inc/Element.hpp"
// #include "../inc/Monster.hpp"
// #include "../inc/Diamond.hpp"
// #include "../inc/Door.hpp"
#include "../inc/Board.hpp"
#include "../inc/Game.hpp"
using namespace std;

int main() {

  // int boardId = 1;
  // Board tablero(boardId);
  // cout<<"Total number of elements created: "<<Element::objectCount<<endl;
  // // tablero.readBoard("0prueba.txt");
  // tablero.createTheMatrix(4,"TRY.txt");
  // tablero.displayBoard();
  // // tablero.getBoardLevel();
  // cout<<"Total number of boards created: "<<Board::boardCount<<endl;
  // cout<<"Total number of elements created: "<<Element::objectCount<<"\n\n";
  // // cout<<"Total number of elements eliminated: "<<Element::deletedCount<<endl;
  // tablero.play();

  Game game1(1);
  game1.addBoard(3,"FIRE.txt","read");
  game1.executeGame();



  return 0;
}
