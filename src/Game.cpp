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
  }
  else if (directive == "create"){
    boards[index].createTheMatrix(index, filename);
  }
  else{
    cout<<"You have not sent a correct directive."<<endl;
  }
}

void Game::run(){
  size_t stage = 0;
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
  // maxcols = COLUMNS-1;
  while (playing == true) {
    if (stage <= (boards.size()-1)) {

      userStage = boards[stage].play(player);

      if (userStage == "KILL") {
        playing = false;
        mvprintw(27,0,"");
        clrtoeol();
        mvaddstr(27, 0, "GAME TERMINATED BY PLAYER");
      }
      else if (userStage == "NEXT") {
        stage++;
        mvprintw(31, 0, "REACHED NEW LEVEL!");
        refresh();
      }
    }
    else {
      playing = false;
      mvprintw(27,0,"");
      clrtoeol();
      mvaddstr(27, 0, "CONGRATULATIONS! YOU FINISHED ALL LEVELS!");
    }
  }
  mvprintw(28, 0, "FINAL SCORE: %d DIAMONDS COLLECTED", player.Diamonds());
  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
}

void Game::loadBoards(){
  srand (time(NULL));
  // Value 5 is hardcoded with Game.hpp should change it
  for (size_t i = 0; i < 2; i++) {
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
