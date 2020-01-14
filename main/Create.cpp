#include "../inc/Board.hpp"
#include <ncurses.h>
#include <ctime>

int main() {
  srand (time(NULL));
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

  int maxlines = LINES-1;
  // int maxcols = COLS-1;

  // board.readBoard(0, "user/j.board");
  board.createTheMatrix(4, "../boards/user/create.board");
  board.displayBoard();

  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
  // board.creator();
  return 0;
}
