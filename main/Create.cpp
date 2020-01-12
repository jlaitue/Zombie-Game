#include "../inc/Board.hpp"
#include <iostream>
#include <ncurses.h>

int main() {
  int level = 0;
  char inputFilename[100];
  int maxcols, maxlines;
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
  mvaddstr(0, maxcols/2-18, "<| TONY STARK'S BOARD CREATOR v1.0 |>");
  mvaddstr(1, maxcols/2-19, "ALEXANDER MORAKHOVSKI | JULIAN LECHUGA");
  mvaddstr(4, 0, "This is the board creator for Ultron's game");
  mvaddstr(5, 0, "You can create a board among 5 levels of difficulty");
  mvaddstr(6, 0, "We require some information to create the board");
  mvaddstr(8, 0, "PRESS ANY KEY TO CONTINUE...");
  refresh();
  getch();
  mvaddstr(2,0,"");
  clrtobot();

  mvaddstr(3, 0, "Enter the file name: ");
  refresh();
  getstr(inputFilename);
  filename = inputFilename;

  mvaddstr(4, 0, "Please enter the difficulty level that you would like to create 1-5: ");
  level = getch() - '0';
  refresh();

  board.createTheMatrix(level, path + filename + ext);

  board.displayBoard();

  mvprintw(maxlines-1, 0, "Game board created with name: %s", inputFilename);
  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT THE CREATOR... ");
  refresh();
  getch();
  endwin();
  exit(0);
  return 0;
}
