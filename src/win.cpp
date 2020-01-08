#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <ncurses.h>
// #include <pdcurses.h>

using namespace std;

void readBoard(char matrix[][40], string filename) {
  string line;
  int rows=0,columns=0;
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0, doorscount = 0;

  fstream inFile;
  inFile.open("../boards/FIRE.txt");

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }

  cout << "Reading board file: "<<filename<<"\n\n";
  while (getline(inFile, line)) {
        for(size_t i = 0; i < line.length(); i++)
        {
          if (line[i] == 'X'){
            matrix[rows][i]='X';
            xcount ++;
          }
          else if (line[i] == '*'){
            matrix[rows][i]='*';
            powcount++;
          }
          else if (line[i] == '$'){
            matrix[rows][i]='$';
            diamcount++;

          }
          else if (line[i] == 'M'){
            matrix[rows][i]='M';
            monscount++;
          }
          else if (line[i] == ' '){
            matrix[rows][i]=' ';
            whitecount++;
          }
          else if (line[i] == '/'){
            matrix[rows][i]='/';
            doorscount++;
          }
        }
        // cout<<"\n";
        rows ++;
    }
    cout<<"Amount X "<<xcount<<"\n";
    cout<<"Amount * "<<powcount<<"\n";
    cout<<"Amount $ "<<diamcount<<"\n";
    cout<<"Amount M "<<monscount<<"\n";
    cout<<"Amount / "<<doorscount<<"\n";
    cout<<"Amount ' ' "<<whitecount<<"\n";

    /* This value of columns is zero because when the .txt file is saved, a new
    line is added at the end. The files have 21 lines, being the last one empty
    which is why the value size of that last line is 0
    */
    // columns = line.size();
    cout<<"Total Rows: "<<rows<<"\n";
    cout<<"Total Columns: "<<40<<"\n";
    cout<<"\n\n";
}

void displayBoard(int rows, int cols, char matrix[][40]){
  for (int i = 0; i < rows; i++) {
    // if(i<10){cout<<i<<"  ";}
    // else{ cout<<i<<" ";}
    for (int j = 0; j < cols; j++) {
      mvaddch(5+i,20+j,matrix[i][j] | A_STANDOUT | COLOR_PAIR(3));
    }
  }
}

int main() {
  int maxcols, maxlines, rows, cols, yshift, xshift;
  char matrix[20][40];
  int userInput;
  char userInputchar;

  readBoard(matrix,"FIRE.txt");
  /* initialize curses */
  initscr();
  // cbreak();
  raw();
  noecho();
  clear();

  /* initialize board */
  yshift = 10;
  xshift = 20;
  maxlines = LINES - 1;
  maxcols = COLS - 1;
  rows = 20;
  cols = 40;

  //Display of gameboard
  matrix[10][20] = 'O';
  displayBoard(rows,cols,matrix);

  mvaddstr(5, cols+25, "PLAYER INFO");
  mvaddstr(6, cols+25, "Diamonds: ");
  mvaddstr(7, cols+25, "Lives: ");
  mvaddstr(8, cols+25, "Teleports: ");

  mvaddstr(10, cols+25, "KEYBOARD COMMANDS");
  mvaddstr(11, cols+25, "T for teleportation");
  mvaddstr(12, cols+25, "K for terminating");
  mvaddstr(13, cols+25, "N for next level");
  // WINDOW * win = newwin(20, 40, 0, 0);
  // mvaddch(yshift+0, xshift, 'X'); //0,0
  // mvaddch(yshift+0, xshift+cols, 'X'); // 0,1
  // mvaddch(yshift+rows, xshift, 'X');//1,0
  // mvaddch(yshift+rows, xshift+cols, 'X');//1,1
  refresh();


  move(27,0);
  printw("Write ESC to finish: ");
  int count = 0;
  while ((userInputchar = getch()) != 'a') {
    move(30,0);
    printw("Character: %c",userInputchar);
    move(27,0);
    printw("Write ESC to finish: ");
    matrix[10-count][20] = ':';
    count++;
    matrix[10-count][20] = 'O';
    displayBoard(rows,cols,matrix);
    refresh();
  }

  /* done */
    mvaddstr(maxlines, 0, "Press any key to quit ");
    refresh();
    getch();
    endwin();

  return 0;
}
