#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <ncurses.h>

using namespace std;

int Game::gameCount = 0;

Game::Game(){
  gameCount++;
  identifier = gameCount;
  gameLevel = 0;
  gameType = 1;
  totalDiamonds = 0;
  // cout<<"Game created"<<"\n";
  // cout<<"Game id: "<<identifier<<"\n";
}

int validateInputValue(int windowLine, char *inputAttribute, int rangeInit, int rangeEnd){
  string inputStr;
  int value;
  inputStr = inputAttribute;
  bool validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);
  bool acceptedInput = false;
  bool rangeInvalid = false;

  while(!acceptedInput){
    while (!validNumber) {
      mvaddstr(windowLine,0,"");
      clrtoeol();
      if(rangeInvalid){
        mvprintw(windowLine, 0, "The value entered must be in range [%d,%d], please try again:  ", rangeInit, rangeEnd);
        rangeInvalid = false;
      }
      else {
        mvprintw(windowLine, 0, "The value you entered is not a number, please try again: ");
      }
      refresh();
      getstr(inputAttribute);
      inputStr = inputAttribute;
      validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);
    }
    istringstream(inputStr) >> value;

    if (value >= rangeInit and value <= rangeEnd) {
      acceptedInput = true;
    }
    else {
      validNumber = false;
      rangeInvalid = true;
    }
  }
  return value;
}

void Game::addBoard(int level, string filename){
  Board board;
  fstream file;
  file.open(filename);

  if (file) {
    // cout<<"READING"<<endl;
    board.readBoard(level, filename);
  }
  else{
    // cout<<"CREATING"<<endl;
    board.createTheMatrix(level, filename);
  }
  boards.push_back(board);
  totalDiamonds = totalDiamonds + board.getNumberDiamonds();
}

void Game::getPlayerInfo(){
  char inputName[100];
  char inputLevel[100];
  char inputGameChoice[100];
  const char *cstr;

  string newName;

  mvaddstr(4, 0, "This is Ultron's board game for saving the planet!");
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

  // We ask for the type of game the user wants
  mvaddstr(5, 0, "Please choose the type of game you want Random (1) ||  User Defined Boards (2): ");
  refresh();
  getstr(inputGameChoice);
  gameType = validateInputValue(5, inputGameChoice, 1, 2);
  mvaddstr(5,0,"");
  clrtoeol();
  mvprintw(5, 0, "GAME DIFFICULTY SELECTED: %d", gameType);

  if (gameType == 2) {
    char inputFilename[100];
    fstream file;

    mvaddstr(5,0,"");
    clrtobot();
    mvprintw(5, 0, "Enter the file name you would like to test: boards/");
    refresh();
    getstr(inputFilename);
    gamefilename = inputFilename;

    file.open("../boards/"+gamefilename);

    while (!file) {
      mvaddstr(5,0,"");
      clrtobot();
      mvprintw(5, 0, "The filename you entered does not exist, try again: ");
      refresh();
      getstr(inputFilename);
      gamefilename = inputFilename;
      file.open("../boards/"+gamefilename);
    }
    mvaddstr(5,0,"");
    clrtoeol();
    mvprintw(5, 0, "Board file selected: %s.board", inputFilename);
  }

  mvaddstr(5, 0, "Please enter the difficulty level that you would like to play from 1 to 9: ");
  refresh();
  getstr(inputLevel);
  gameLevel = validateInputValue(5, inputLevel, 1, 9);
  mvaddstr(5,0,"");
  clrtoeol();
  mvprintw(5, 0, "GAME DIFFICULTY SELECTED: %d", gameLevel);

  mvaddstr(LINES-1, 0, "PRESS ANY KEY TO BEGIN THE GAME...");
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

  if (gameType == 1) {
    loadBoards();
  }
  else {
    loadUserBoards();
  }

  noecho();
  while (playing == true) {
    if (stage <= (boards.size()-1)) {
      mvprintw(3, 20, "Game stage %d/%d", stage+1, boards.size());
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

  mvprintw(28, maxcols/2-25, "FINAL SCORE: %d DIAMONDS COLLECTED OUT OF %d", player.Diamonds(), totalDiamonds);
  if (player.Diamonds() == totalDiamonds) {
    mvprintw(29, maxcols/2-25, "YOU REACHED THE HIGHEST SCORE, CONGRATS MATE!", player.Diamonds(), totalDiamonds);
  }
  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
}

void Game::loadBoards(){
  srand (time(NULL));
  // The level selected defines the number of boards to play in the game
  int numberBoards = gameLevel;
  for (int i = 0; i < numberBoards; i++) {

    // The game level selected also defines the difficulty for each board
    int level = gameLevel;
    string path = "../boards", ext = ".board", name = "board";
    string filename = "/level_"+to_string(gameLevel)+"/"+name+to_string(i)+ext;

    // If the game level selected is bigger than 5 then a random difficulty
    // level for each board is selected among the 3 highest levels available
    if (gameLevel>5) {
      //Maybe change this to 6 to have the highest difficulty level
      level = rand() %6 + 3;
    }

    addBoard(level, path+filename);
  }
}

void Game::loadUserBoards(){
  srand (time(NULL));
  string path = "../boards/";
  addBoard(gameLevel, path+gamefilename);
}

Game::~Game(){
  // cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
