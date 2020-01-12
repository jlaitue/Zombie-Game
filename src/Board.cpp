#include "../inc/Board.hpp"
#include "../inc/Element.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <ncurses.h>
#include <sstream>

using namespace std;

int Board::boardCount = 0;

Board::Board(){
  rowOrigin = 5;
  colOrigin = 20;
  infoBoxIdent = 10;
  // cout<<"Board created"<<endl;
}

Board::Board(int id): identifier(id){
  cout<<"Board created"<<"\n";
  cout<<"Board id: "<<identifier<<"\n";
  boardCount++;
}

string columnOrientation(){
    if (rand() % 2 == 0)
        return "horizontal";
    else return "vertical";
}

void Board::positionObjects(int nDiam, int nMons, int nDoors, int nStars, int nWalls){
  // srand (time(NULL));
  int emptyRows = n-2;
  int emptyCols = m-2;
  while(nWalls != 0){
      string direction = columnOrientation();
      char s = 'X';
      int x1 = rand() %emptyRows + 1;
      int y1 = rand() %emptyCols + 1;

      // cout<<"Column orientation: "<<direction<<"\n";

      //If beginning point is empty proceed
      if(matrix[x1][y1].getSymbol() == ' '){
        // cout<<"Wall number: "<<nWalls<<"\n";
        // cout<<"Coords: "<<x1<<" "<<y1<<"\n";

        if(direction == "vertical"){
          int length = rand() %emptyRows + 1;
          // cout<<"Length: "<<length<<"\n\n";
          for (int i = 0; i < length; i++) {
            if (matrix[x1+i][y1].getSymbol() == ' ') {
              matrix[x1+i][y1].updateSymbol(s);
            }
            else break;
          }
          nWalls --;
        }

        else if(direction == "horizontal"){
          int length = rand() %emptyCols + 1;
          // cout<<"Length: "<<length<<"\n\n";
          for (int i = 0; i < length; i++) {
            if (matrix[x1][y1+i].getSymbol() == ' ') {
              matrix[x1][y1+i].updateSymbol(s);
            }
            else break;
          }
          nWalls --;
        }

      }
    }

  while(nDiam != 0){
    int row = rand() %emptyRows + 1;
    int column = rand() %emptyCols + 1;
    if(matrix[row][column].getSymbol() == ' '){
      matrix[row][column].updateElement(row,column,"diamond",'$');
      nDiam --;
    }
  }

  while(nMons != 0){
    int row = rand() %emptyRows + 1;
    int column = rand() %emptyCols + 1;
    if(matrix[row][column].getSymbol() == ' '){
      matrix[row][column].updateElement(row,column,"monster",'M');
      nMons --;
    }
  }

  while(nStars != 0){
    int row = rand() %emptyRows + 1;
    int column = rand() %emptyCols + 1;
    if(matrix[row][column].getSymbol() == ' '){
      matrix[row][column].updateElement(row,column,"power", '*');
      nStars --;
    }
  }

  while(nDoors != 0){
    int doorCoordCase = rand() %4 + 1;
    switch (doorCoordCase) {
      case 1:{
        int row = rand() %emptyRows + 1;
        int column = 0;
        matrix[row][column].updateElement(row,column,"door",'#');
        break;
      }
      case 2:{
        int row = 0;
        int column = rand() %emptyCols + 1;
        matrix[row][column].updateElement(row,column,"door",'#');
        break;
      }
      case 3:{
        int row = rand() %emptyRows + 1;
        int column = 39;
        matrix[row][column].updateElement(row,column,"door",'#');
        break;
      }
      case 4:{
        int row = 19;
        int column = rand() %emptyCols + 1;
        matrix[row][column].updateElement(row,column,"door",'#');
        break;
      }
    }
    nDoors--;
  }
}

void colorCoding(char element, int &colorCode){
  if (element == 'O') {
    colorCode = 1;
  }
  else if (element == 'M') {
    colorCode = 2;
  }
  else if (element == '*') {
    colorCode = 3;
  }
  else if (element == '$') {
    colorCode = 4;
  }
  else if (element == '.') {
    colorCode = 5;
  }
  else if (element == '#') {
    colorCode = 2;
  }
  else if (element == '+') {
    colorCode = 5;
  }
  else{
    colorCode = 6;
  }
}

void Board::displayBoard(){
  char element;
  int colorCode;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      element = matrix[i][j].getSymbol();
      colorCoding(element, colorCode);
      mvaddch(rowOrigin+i,colOrigin+j, element | COLOR_PAIR(colorCode));
    }
  }
}

void Board::readBoard(int l, string filename){
  level = l;
  boardName = filename;
  // cout<<"Operation READING..."<<"\n";
  string line;
  int rows=0;
  // int columns=0;
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0, doorscount = 0;

  fstream inFile;
  inFile.open("../boards/"+filename);

  if (!inFile) {
    cerr << "Unable to open file " +filename;
    exit(1);   // call system to stop
  }
  // cout << "Reading board file: "<<filename<<"\n\n";
  while (getline(inFile, line)) {
        // cout<<"Analyzing row: "<<rows<<"\n";
        // cout<<line;
        // cout<<line.size();
        for(size_t i = 0; i < line.length(); i++)
        {
          // cout<<"Fila "<<i<<"\n";
          if (line[i] == 'X'){
            // cout<<"FOUND AN X ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            // idtag(id), xcoord(x), ycoord(y),type(t),symbol(s)
            matrix[rows][i].updateElement(rows,i,"wall",'X');
            xcount ++;
          }
          else if (line[i] == '*'){
            // cout<<"FOUND A POWERUP ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"power",'*');
            powcount++;
          }
          else if (line[i] == '$'){
            // cout<<"FOUND A DIAMOND ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"diam",'$');
            diamcount++;

          }
          else if (line[i] == 'M'){
            // cout<<"FOUND A MONSTER ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            // matrix[rows][i].updateElement(rows,i,"mons",'M');
            monscount++;
          }
          else if (line[i] == ' '){
            // cout<<"FOUND EMPTY SPACE ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"space",' ');
            whitecount++;
          }
          // else if (line[i] == 'J'){
          //   // cout<<"FOUND PLAYER ";
          //   // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
          //   Player player1(1,rows,i,"player",'J');
          //   matrix[rows][i] = player1;
          // }
          else if (line[i] == '#'){
            // cout<<"FOUND DOOR ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"door",'#');
            doorscount++;
          }
        }
        // cout<<"\n";
        rows ++;
    }
    // cout<<"Amount X "<<xcount<<"\n";
    // cout<<"Amount * "<<powcount<<"\n";
    // cout<<"Amount $ "<<diamcount<<"\n";
    // cout<<"Amount M "<<monscount<<"\n";
    // cout<<"Amount / "<<doorscount<<"\n";
    // cout<<"Amount ' ' "<<whitecount<<"\n";

    /* This value of columns is zero because when the .txt file is saved, a new
    line is added at the end. The files have 21 lines, being the last one empty
    which is why the value size of that last line is 0
    */
    // columns = line.size();
    // columns = m;
    // cout<<"Total Rows: "<<rows<<"\n";
    // cout<<"Total Columns: "<<columns<<"\n";
    // cout<<"\n\n";
}

void Board::createTheMatrix(int l, string file){
  level = l;
  boardName = file;
  ofstream myfile(file);

// Creation of string matrix with elements of board
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        //Creation of horizontal outer walls
        if(i==0 or i == n-1){
          matrix[i][j].updateElement(i,j,"wall",'X');
        }
        //Creation of vertical outer walls
        else if(i > 0 and (j == 0 or j == m-1)){
          matrix[i][j].updateElement(i,j,"wall",'X');
        }
        else if(i > 0 and (j > 0 and j < m-1)){
          matrix[i][j].updateElement(i,j,"space",' ');
        }
      }
    }

/*
Positioning of different amount of elements depending on difficulty level
chosen
*/
switch (level) {
  case 1:
    {
      // cout<<"Creation of board of level 1\n\n";
      int nDiam = 5, nMons = 1, nStars = 0, nDoors = 5, nWalls = 2;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 2:
    {
      // cout<<"Creation of board of level 2\n\n";
      int nDiam = 5, nMons = 1, nStars = 1, nDoors = 4, nWalls = 2;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 3:
    {
      // cout<<"Creation of board of level 3\n\n";
      int nDiam = 4, nMons = 3, nStars = 2, nDoors = 3, nWalls = 3;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 4:
    {
      // cout<<"Creation of board of level 4\n\n";
      int nDiam = 4, nMons = 4, nStars = 3, nDoors = 2, nWalls = 3;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 5:
    {
      // cout<<"Creation of board of level 5\n\n";
      int nDiam = 8, nMons = 5, nStars = 4, nDoors = 1, nWalls = 5;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  default:
    {
      // cout<<"Creation of board of level default\n\n";
      int nDiam = 15, nMons = 10, nStars = 10, nDoors = 1, nWalls = 10;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }

}

// Writting of matrix previously created to .txt file
  if (myfile.is_open()) {
    // cout<<"Writting to board file: "<< filename<<"\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        myfile<<matrix[i][j].getSymbol();
      }
      myfile<<"\n";
    }
    myfile.close();
    // cout<<"Done writting."<<"\n";
  }
  else {
    // cout << "Unable to open file for creation";
  }
}

string Board::getBoardName(){
  return boardName;
}

bool Board::openDoor(){
  bool found = false;
  for (int i = 0; i < n; i++) {
    if(found){break;}
    for (int j = 0; j < m; j++) {
      if(matrix[i][j].getSymbol() == '#'){
        matrix[i][j].updateSymbol('+');
        found = true;
        break;
      }
    }
  }
  return found;
}

void Board::validateMovement(int &rowPosition, int &colPosition, char nextStr,
  bool &movementValid, bool &nextBoard, Player &player, int moveCase){
    int maxcols = COLS-1;

  if (nextStr == 'X') {
    mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "INVALID MOVE. THERE IS AN OBSTACLE!");
  }

  else if (nextStr == '#') {
    mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "DOOR CLOSED. GET A DIAMOND TO OPEN IT!");
  }

  else if (nextStr == '+'){
    nextBoard = 1;
  }

  else{
    movementValid = 1;
    if(nextStr == '$'){
      player.incrementDiamonds();
      if(openDoor()) {
        mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOUR DIAMOND OPENED A DOOR!");
      }
      else{
        mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU FOUND A DIAMOND!");
      }
    }
    else if(nextStr == '*'){
      player.incrementPowerups();
      mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU FOUND A TELEPORTER!");
    }
    else if(nextStr == 'M'){
      player.decrementLives();
      mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU JUST GOT EATEN!");
      if(player.Lives() == 0){
        mvprintw(rowOrigin+2, maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU ARE DEAD! :C");
      }
    }
    switch (moveCase) {
      case 1:{
        rowPosition --;
        // cout<<"MOVING UP"<<endl;
        break;
      }
      case 2:{
        rowPosition ++;
        // cout<<"MOVING DOWN"<<endl;
        break;
      }
      case 3:{
        colPosition++;
        // cout<<"MOVING RIGHT"<<endl;
        break;
      }
      case 4:{
        colPosition--;
        // cout<<"MOVING LEFT"<<endl;
        break;
      }
      case 5:{
        colPosition++;
        rowPosition--;
        // cout<<"MOVING DIAGONALLY UP R "<<endl;
        break;
      }
      case 6:{
        colPosition--;
        rowPosition--;
        // cout<<"MOVING DIAGONALLY UP L "<<endl;
        break;
      }
      case 7:{
        colPosition--;
        rowPosition++;
        // cout<<"MOVING DIAGONALLY DOWN L"<<endl;
        break;
      }
      case 8:{
        colPosition++;
        rowPosition++;
        // cout<<"MOVING DIAGONALLY DOWN R"<<endl;
        break;
      }
    }
  }
}

void Board::clearMonsters(){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if(matrix[i][j].getSymbol() == 'M'){
        matrix[i][j].updateElement(i,j,"space",' ');
      }
    }
  }
}

void Board::moveMonsters(int emptyRows, int emptyCols){
  int monsters = level;
  int row = 0;
  int column = 0;
  char c;
  clearMonsters();
  for (int i = 0; i < monsters; i++) {
    c = matrix[row][column].getSymbol();
    while ( c == 'X' or c == '*' or c == '$' or c == 'M') {
      row = rand() %emptyRows + 1;
      column = rand() %emptyCols + 1;
      c = matrix[row][column].getSymbol();
    }
    matrix[row][column].updateElement(row,column,"monster",'M');
  }
}

string Board::play(Player &player){
  string move = "";
  const char *charedPlayerName = player.getName().c_str();
  // Initial player position which probably should be changed to a randomized pos
  int rowPosition = n/2;
  int colPosition = m/2;
  char userInput;
  int maxcols = COLS-1;

  colOrigin = maxcols/2-m;

  // Square area in which the player can teleport to
  int emptyRows = n-2;
  int emptyCols = m-2;

  matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player",'O');
  // matrix[rowPosition][colPosition] = player;

  //Clear the contents of the previous window but maintaining the header info
  mvaddstr(4,0,"");
  clrtobot();

  displayBoard();
  mvprintw(rowOrigin+5, maxcols/2+infoBoxIdent, "PLAYER | %s |",charedPlayerName);
  mvprintw(rowOrigin+6, maxcols/2+infoBoxIdent, "Diamonds: %d", player.Diamonds());
  mvprintw(rowOrigin+7, maxcols/2+infoBoxIdent, "Lives: %d", player.Lives());
  mvprintw(rowOrigin+8, maxcols/2+infoBoxIdent, "Teleports: %d", player.Powerups());

  mvaddstr(rowOrigin+10, maxcols/2+infoBoxIdent, "KEYBOARD COMMANDS");
  mvaddstr(rowOrigin+11, maxcols/2+infoBoxIdent, "Press T to teleport");
  mvaddstr(rowOrigin+12, maxcols/2+infoBoxIdent, "Press K to exit");
  mvaddstr(rowOrigin+13, maxcols/2+infoBoxIdent, "Press W A S D for lineal movement");
  mvaddstr(rowOrigin+14, maxcols/2+infoBoxIdent, "Press Q E Z C for diagonal movement");

  mvaddstr(rowOrigin, maxcols/2+infoBoxIdent, "ENTER NEXT MOVE: ");
  while (move != "STOP") {
    bool movementValid = 0;
    bool nextBoard = 0;
    if (player.Lives() > 0) {
      userInput = getch();
      mvprintw(rowOrigin, maxcols/2+infoBoxIdent, "ENTER NEXT MOVE: %c", userInput);
      mvprintw(rowOrigin+2, maxcols/2+infoBoxIdent,"");
      clrtoeol();
      refresh();

      moveMonsters(emptyRows, emptyCols);
      matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"space",'.');

      if (userInput == 'k' or userInput == 'K'){
        mvprintw(rowOrigin, maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvprintw(rowOrigin, maxcols/2+infoBoxIdent, "GAME OVER!");
        refresh();
        return "KILL";
      }

      else if (userInput == 'w' or userInput == 'W'){
        char nextStr = matrix[rowPosition-1][colPosition].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 1);
      }

      else if (userInput == 's' or userInput == 'S'){
        char nextStr = matrix[rowPosition+1][colPosition].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 2);
      }

      else if (userInput == 'd' or userInput == 'D'){
        char nextStr = matrix[rowPosition][colPosition+1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 3);
      }

      else if (userInput == 'a' or userInput == 'A'){
        char nextStr = matrix[rowPosition][colPosition-1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 4);
      }

      else if (userInput == 'e' or userInput == 'E'){
        char nextStr = matrix[rowPosition-1][colPosition+1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 5);
      }

      else if (userInput == 'q' or userInput == 'Q'){
        char nextStr = matrix[rowPosition-1][colPosition-1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 6);
      }

      else if (userInput == 'z' or userInput == 'Z'){
        char nextStr = matrix[rowPosition+1][colPosition-1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 7);
      }

      else if (userInput == 'c' or userInput == 'C'){
        char nextStr = matrix[rowPosition+1][colPosition+1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 8);
      }

      else if (userInput == 't' or userInput == 'T'){
        if (player.Powerups() > 0) {
          movementValid = 1;
          int row = 0;
          int column = 0;
          while (matrix[row][column].getSymbol() == 'X' or matrix[row][column].getSymbol() == 'M') {
            row = rand() %emptyRows + 1;
            column = rand() %emptyCols + 1;
          }
          player.decrementPowerups();
          rowPosition = row;
          colPosition = column;
        }
        else{
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU DO NOT HAVE ANY TELEPORTERS. SORRY!");
        }
      }

      else if (userInput == 'n' or userInput == 'N'){
        if (player.Powerups() >= 5) {
          bool found = false;
          for (int i = 0; i < n; i++) {
            if(found){break;}
            for (int j = 0; j < m; j++) {
              if(matrix[i][j].getSymbol() == '+'){
                found = true;
                break;
              }
            }
          }
          if (found) {
            for (size_t i = 0; i < 5; i++) {
              player.decrementPowerups();
            }
            nextBoard = 1;
          }
          else{
            mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU NEED TO OPEN A DOOR FIRST!");
          }
        }
        else{
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "NOT ENOUGH POWER TO CHANGE BOARD!");
        }
      }

      else if (userInput == 'b' or userInput == 'B'){
        if (player.Diamonds() >= 3) {
          movementValid = 1;
          player.incrementLives();
          for (size_t i = 0; i < 2; i++) {
            player.decrementDiamonds();
          }
        }
        else{
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "NOT ENOUGH DIAMONDS TO BUY A LIFE");
        }
      }

      else{
        mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "TRY A VALID KEYBOARD INPUT");
      }

      if (nextBoard){
        return "NEXT";
      }

      if (movementValid) {
        matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player",'O');
        displayBoard();
        mvprintw(rowOrigin+6, maxcols/2+infoBoxIdent, "Diamonds: %d", player.Diamonds());
        mvprintw(rowOrigin+7, maxcols/2+infoBoxIdent, "Lives: %d", player.Lives());
        mvprintw(rowOrigin+8, maxcols/2+infoBoxIdent, "Teleports: %d", player.Powerups());
      }
    }

    else{
      return "KILL";
    }
  }
  return "CONTINUE";
}

Board::~Board(){
  // cout<<"Board "<<identifier<<" destroyed."<<"\n";
}
