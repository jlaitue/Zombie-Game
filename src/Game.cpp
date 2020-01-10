#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <ctime>
#include <ncurses.h>

using namespace std;

int Game::gameCount = 0;

Game::Game(){
  gameCount++;
  identifier = gameCount;
  // cout<<"Game created"<<"\n";
  // cout<<"Game id: "<<identifier<<"\n";
}

void Game::addBoard(int index, string filename, string directive){
  if (directive == "read") {
    Board board;
    board.readBoard(filename);
    boards.push_back(board);
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
  raw();
  noecho();
  clear();
  start_color();

  init_pair(1,COLOR_GREEN, COLOR_BLACK);
  init_pair(2,COLOR_RED, COLOR_BLACK);
  init_pair(3,COLOR_YELLOW, COLOR_BLACK);
  init_pair(4,COLOR_BLUE, COLOR_BLACK);
  init_pair(5,COLOR_CYAN, COLOR_BLACK);
  init_pair(6,COLOR_WHITE, COLOR_BLACK);

  maxlines = LINES-1;
  while (playing == true) {
    userStage = boards[stage].play(player);
    if (userStage == "KILL") {
      playing = false;
      mvaddstr(maxlines, 0, "PRESS ANY KEY TO TERMINATE... ");
      refresh();
      getch();
      endwin();
      exit(0);
    }
    else if (userStage == "NEXT") {
      stage++;
      mvprintw(31, 0, "REACHED NEW LEVEL!");
      refresh();
    }
  }

}

void Game::loadBoards(){
  srand (time(NULL));
  // Value 5 is hardcoded with Game.hpp should change it
  for (size_t i = 0; i < 8; i++) {
    // int boardId = rand() %19 + 2;
    string s;
    s = to_string(i);
    // cout<<"Name: "<<boardId<<endl;
    addBoard(i, s+"prueba.txt", "read");
  }
}

Game::~Game(){
  // cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
