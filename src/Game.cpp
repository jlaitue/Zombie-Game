#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include <iostream>

using namespace std;

int Game::gameCount = 0;

Game::Game(int id): identifier(id){
  cout<<"Game created"<<"\n";
  cout<<"Game id: "<<identifier<<"\n";
  gameCount++;
}

void Game::addBoard(int level, string filename, string directive){
  if (directive == "read") {
    board.readBoard(filename);
  }
  else if (directive == "create"){
    board.createTheMatrix(level, filename);
  }
  else{
    // There is a bug that needs fixing, an empty BOARD is shown in this case
    cout<<"You have not sent a correct directive."<<endl;
  }
}

void Game::runGame(){
  board.play();
}

void Game::getGameLevel(){
  cout<<"Game with id "<<identifier<<" has level: "<<level<<"\n";
}

Game::~Game(){
  cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
