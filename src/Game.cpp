#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <ncurses.h>

using namespace std;

int Game::gameCount = 0;

Game::Game(){
  gameCount++;
  identifier = gameCount;
  // cout<<"Game created"<<"\n";
  // cout<<"Game id: "<<identifier<<"\n";
}
// Fix inconsistency with level and index fro createTheMatrix
void Game::addBoard(int index, string filename, string directive){
  if (directive == "read") {
    boards[index].readBoard(filename);
    // boards[index].displayBoard();
  }
  else if (directive == "create"){
    boards[index].createTheMatrix(index, filename);
    // boards[index].displayBoard();
  }
  else{
    // There is a bug that needs fixing, an empty BOARD is shown in this case
    cout<<"You have not sent a correct directive."<<endl;
  }
}

void Game::run(){

  int stage = 0;
  bool playing = true;
  string userStage = "";
  int maxlines;

  initscr();
  // cbreak();
  raw();
  noecho();
  clear();


  maxlines = LINES-1;
  while (playing == true) {
    userStage = boards[stage].play();
    if (userStage == "KILL") {
      // cout<<"GAME METHOD runGame() TERMINATED BY USER."<<endl;
      playing = false;
      mvaddstr(maxlines, 0, "Press any key to quit ");
      refresh();
      getch();
      endwin();
      exit(0);
    }
    else if (userStage == "NEXT") {
      cout<<"BOARD CHANGED BY USER."<<endl;
      cout<<"\n                   LOADING NEXT BOARD...\n\n";
      stage++;
    }
  }

}

void Game::loadBoards(){
  srand (time(NULL));
  // Value 5 is hardcoded with Game.hpp should change it
  for (size_t i = 0; i < 5; i++) {
    int boardId = rand() %19 + 2;
    stringstream ss;
    ss<<boardId;
    string s;
    ss>>s;
    addBoard(i, s+"prueba.txt", "read");
  }
}

Game::~Game(){
  // cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
