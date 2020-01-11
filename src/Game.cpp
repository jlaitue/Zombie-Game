#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

int Game::gameCount = 0;

Game::Game(){
  gameCount++;
  identifier = gameCount;
  gameLevel = 0;
  // cout<<"Game created"<<"\n";
  // cout<<"Game id: "<<identifier<<"\n";
}

void Game::addBoard(int level, string filename){
  Board board;
  fstream file;
  file.open(filename);

  if (file) {
    // cout<<"READING"<<endl;
    board.readBoard(filename);
  }
  else{
    // cout<<"CREATING"<<endl;
    board.createTheMatrix(level, filename);
  }
  boards.push_back(board);
}

void Game::getPlayerInfo(){
  char inputName[100];
  char inputLevel;
  const char *cstr;

  string newName;
  bool valid = false;

  mvaddstr(4, 0, "This is a fun board game in which you must collect diamonds");
  mvaddstr(5, 0, "You should avoid getting eaten by monsters and finish all levels!");
  mvaddstr(6, 0, "Before we begin we need some information to create a game suited to your liking");
  mvaddstr(8, 0, "PRESS ANY KEY TO CONTINUE...");
  refresh();
  getch();
  mvaddstr(2,0,"");
  clrtobot();

  mvaddstr(4, 0, "First enter your name: ");
  refresh();
  getstr(inputName);
  newName = inputName;
  cstr = player.updateName(newName).c_str();

  mvprintw(4, 0, "WELCOME TO THE AVENGERS TOWER | %s | ", cstr);
  mvaddstr(5, 0, "Please enter the difficulty level that you would like to play from 1 to 9: ");
  inputLevel = getch();
  refresh();

  while(!valid){
    mvaddstr(5,0,"");
    clrtoeol();
    if (inputLevel == '1' || inputLevel == '2' || inputLevel == '3'
       || inputLevel == '4' || inputLevel == '5' || inputLevel == '6'
       || inputLevel == '7' || inputLevel == '8' || inputLevel == '9') {
      valid = true;
      mvprintw(5, 0, "GAME DIFFICULTY SELECTED: %c", inputLevel);
    }
    else{
      mvprintw(5, 0, "The value you entered is not valid integer, please try again: %c", inputLevel);
      refresh();
      inputLevel = getch();
    }
  }
  /* We need to substract the ASCII value of char '0' in order to obtain the
  actual integer value of the number the user introduced as input */
  gameLevel = inputLevel - '0';
  mvaddstr(8, 0, "PRESS ANY KEY TO BEGIN THE GAME...");
  refresh();
  getch();
}

void Game::run(){
  size_t stage = 0;
  bool playing = true;
  string userStage = "";
  int maxlines, maxcols;

  initscr();
  raw();
  clear();
  start_color();

  init_pair(1,COLOR_GREEN, COLOR_BLACK);
  init_pair(2,COLOR_RED, COLOR_BLACK);
  init_pair(3,COLOR_YELLOW, COLOR_BLACK);
  init_pair(4,COLOR_BLUE, COLOR_BLACK);
  init_pair(5,COLOR_CYAN, COLOR_BLACK);
  init_pair(6,COLOR_WHITE, COLOR_BLACK);

  maxlines = LINES-1;
  maxcols = COLS-1;

  mvaddstr(0, maxcols/2-15, "<| ULTRON'S BOARD GAME v1.0 |>");
  mvaddstr(1, maxcols/2-19, "ALEXANDER MORAKHOVSKI | JULIAN LECHUGA");

  getPlayerInfo();
  loadBoards();

  noecho();
  while (playing == true) {
    if (stage <= (boards.size()-1)) {

      userStage = boards[stage].play(player);

      if (userStage == "KILL") {
        playing = false;
        mvprintw(27, 0,"");
        clrtoeol();
        mvaddstr(27, maxcols/2-25, "GAME TERMINATED BY PLAYER");
      }
      else if (userStage == "NEXT") {
        stage++;
        mvprintw(7, maxcols/2+10, "REACHED NEW LEVEL!");
        refresh();
      }
    }
    else {
      playing = false;
      mvprintw(27, 0,"");
      clrtoeol();
      mvaddstr(27, maxcols/2-25, "CONGRATULATIONS! YOU COMPLETED ALL LEVELS!");
    }
  }

  mvprintw(28, maxcols/2-25, "FINAL SCORE: %d DIAMONDS COLLECTED", player.Diamonds());
  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
}

void Game::loadBoards(){
  srand (time(NULL));
  for (int i = 0; i < gameLevel; i++) {
    // int boardLevel = 0;
    // switch (gameLevel) {
    //   case 1:
    //   boardLevel = 1;
    //   case 2:
    //   boardLevel = 1;
    //   case 3:
    //   boardLevel = 1;
    //   case 4:
    //   boardLevel = 1;
    //   case 5:
    //   boardLevel = 1;
    //   default: return true;
    // }
    // int boardId = rand() %19 + 2;
    // cout<<s<<endl;
    string path = "../boards", ext = ".board", name = "board";
    string filename = "/level_"+to_string(gameLevel)+"/"+to_string(i)+board+ext;
    addBoard(gameLevel, path+filename);
  }
}

Game::~Game(){
  // cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
