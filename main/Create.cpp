#include "../inc/Board.hpp"
#include <iostream>
#include <ncurses.h>
#include <sstream>


int validateInputValue(int windowLine, char *inputAttribute){

  string inputStr;
  int value;
  inputStr = inputAttribute;
  bool validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);

  while (!validNumber) {
    mvaddstr(windowLine,0,"");
    clrtoeol();
    mvprintw(windowLine, 0, "The value you entered is not a number, please try again: ");
    refresh();
    getstr(inputAttribute);
    inputStr = inputAttribute;
    validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);
  }

  istringstream(inputStr) >> value;
  return value;
}

int main() {
  char inputFilename[100];
  char inputAttribute[100];

  int maxcols, maxlines;
  int requestedBoards = 0;
  int requestedDiamonds;
  int requestedMonsters;
  int requestedDoors;
  int requestedPowerups;

  string path = "../boards/user/";
  string ext = ".board";
  string filename;

  Board board;

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

  maxcols = COLS-1;
  maxlines = LINES-1;
  //Header info and instructions
  mvaddstr(0, maxcols/2-18, "<| TONY STARK'S BOARD CREATOR v1.0 |>");
  mvaddstr(1, maxcols/2-19, "ALEXANDER MORAKHOVSKI | JULIAN LECHUGA");
  mvaddstr(4, 0, "This is the board creator for Ultron's game");
  mvaddstr(5, 0, "In this version 1.0 the size of the board is fixed to 20x40 elements");
  mvaddstr(6, 0, "You can create a board with different amount of elements");
  mvaddstr(7, 0, "The elements of the board include Monsters, Diamonds, Doors and Powerups");
  mvaddstr(8, 0, "Let's begin creating!");
  mvaddstr(10, 0, "PRESS ANY KEY TO CONTINUE...");
  refresh();
  getch();
  mvaddstr(2,0,"");
  clrtobot();

  // User input of number of boards to create
  mvaddstr(3, 0, "Please enter the number of boards you would like to create: ");
  refresh();
  getstr(inputAttribute);
  requestedBoards = validateInputValue(3, inputAttribute);
  mvaddstr(3,0,"");
  clrtoeol();
  mvprintw(3, 0, "Number of boards to create: %d", requestedBoards);

  for (int i = 0; i < requestedBoards; i++) {
    mvaddstr(3,0,"");
    clrtobot();
    mvprintw(3, 0, "Enter the file name for board %d/%d: ",i+1,requestedBoards);
    refresh();
    getstr(inputFilename);
    filename = inputFilename;
    mvaddstr(3,0,"");
    clrtoeol();
    mvprintw(3, 0, "File name: %s.board", inputFilename);

    // User input of number of diamonds for board
    mvaddstr(5, 0, "Please enter the number of diamonds: ");
    refresh();
    getstr(inputAttribute);
    requestedDiamonds = validateInputValue(5, inputAttribute);
    mvaddstr(5,0,"");
    clrtoeol();
    mvprintw(5, 0, "Number of diamonds: %d", requestedDiamonds);

    // User input of number of Monsters for board
    mvaddstr(7, 0, "Please enter the number of monsters: ");
    refresh();
    getstr(inputAttribute);
    requestedMonsters = validateInputValue(7, inputAttribute);
    mvaddstr(7,0,"");
    clrtoeol();
    mvprintw(7, 0, "Number of monsters: %d", requestedMonsters);

    // User input of number of Powerups for board
    mvaddstr(9, 0, "Please enter the number of powerups: ");
    refresh();
    getstr(inputAttribute);
    requestedPowerups = validateInputValue(9, inputAttribute);
    mvaddstr(9,0,"");
    clrtoeol();
    mvprintw(9, 0, "Number of powerups: %d", requestedPowerups);

    // User input of number of Powerups for board
    mvaddstr(11, 0, "Please enter the number of doors: ");
    refresh();
    getstr(inputAttribute);
    requestedDoors = validateInputValue(11, inputAttribute);
    mvaddstr(11,0,"");
    clrtoeol();
    mvprintw(11, 0, "Number of doors: %d", requestedDoors);

    board.updateNumberDiamonds(requestedDiamonds);
    board.updateNumberMonsters(requestedMonsters);
    board.updateNumberDoors(requestedDoors);
    board.updateNumberPowerups(requestedPowerups);

    mvaddstr(maxlines, 0, "PRESS ANY KEY TO CREATE THE BOARD... ");
    getch();

    srand (time(NULL));
    board.createTheMatrix(0, path + filename + ext);
    mvaddstr(3,0,"");
    clrtobot();
    mvprintw(3, 0, "Game board: %s.board", inputFilename);
    board.displayBoard();
    mvaddstr(maxlines, 0, "PRESS ANY KEY TO CONTINUE... ");
    refresh();
    getch();

  }


  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT THE CREATOR... ");
  refresh();
  getch();
  endwin();
  exit(0);
  return 0;
}
