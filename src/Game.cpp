#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

int Game::gameCount = 0;

Game::Game(int id): identifier(id){
  cout<<"Game created"<<"\n";
  cout<<"Game id: "<<identifier<<"\n";
  gameCount++;
}

void Game::getGameLevel(){
  cout<<"Game with id "<<identifier<<" has level: "<<level<<"\n";
}

Game::~Game(){
  cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
