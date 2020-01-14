#include "../inc/Board.hpp"
#include "../inc/Element.hpp"
#include "../inc/Player.hpp"
#include "../inc/Monster.hpp"
#include "../inc/Helper.h"
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
  infoBoxIdent = 5;
  availableDiamonds = 0;
  availableMonsters = 0;
  availableDoors = 0;
  availablePowerups = 0;
  availableWalls = 0;
  virusModeBoard = false;
  helpShown = false;
  // cout<<"Board created"<<endl;
}

Board::Board(int id): identifier(id){
  cout<<"Board created"<<"\n";
  cout<<"Board id: "<<identifier<<"\n";
  boardCount++;
}

void Board::switchVirusMode(){
    virusModeBoard = !virusModeBoard;
}

int Board::getNumberDiamonds(){
  return availableDiamonds;
}

void Board::positionObjects(){
  int nDiam = availableDiamonds;
  int nMons = availableMonsters;
  int nDoors = availableDoors;
  int nStars = availablePowerups;
  int nWalls = availableWalls;

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
      Monster monster;
      monster.updateMonsterCoords(row, column);
      monsters.push_back(monster);
      // matrix[row][column].updateElement(row,column,"monster",'M');
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
  //Display of monsters position
  for (size_t i = 0; i < monsters.size(); i++) {
    int monsRow = monsters[i].getMonsterX();
    int monsCol = monsters[i].getMonsterY();
    char monsSymbol = monsters[i].getSymbol();
    mvaddch(rowOrigin+monsRow,colOrigin+monsCol, monsSymbol | COLOR_PAIR(2));
  }
}

void Board::readBoard(int l, string filename){
  level = l;
  boardName = filename;
  // cout<<"Operation READING..."<<"\n";
  string line;
  int rows=0;
  // int columns=0;
  int xcount = 0, powcount=0, whitecount=0, doorscount = 0;

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
            availableDiamonds++;

          }
          else if (line[i] == 'M'){
            Monster monster;
            // cout<<"FOUND A MONSTER ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            // matrix[rows][i].updateElement(rows,i,"mons",'M');
            monster.updateMonsterCoords(rows, i);
            monsters.push_back(monster);
            availableMonsters++;
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
    // cout<<"Amount $ "<<availableDiamonds<<"\n";
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
      availableDiamonds = 5;
      availableMonsters = 3;
      availablePowerups = 0;
      availableDoors = 5;
      availableWalls = 3;
      positionObjects();
      break;
    }
  case 2:
    {
      // cout<<"Creation of board of level 2\n\n";
      availableDiamonds = 5;
      availableMonsters = 3;
      availablePowerups = 1;
      availableDoors = 4;
      availableWalls = 3;
      positionObjects();
      break;
    }
  case 3:
    {
      // cout<<"Creation of board of level 3\n\n";
      availableDiamonds = 4;
      availableMonsters = 4;
      availablePowerups = 2;
      availableDoors = 3;
      availableWalls = 3;
      positionObjects();
      break;
    }
  case 4:
    {
      // cout<<"Creation of board of level 4\n\n";
      availableDiamonds = 4;
      availableMonsters = 5;
      availablePowerups = 3;
      availableDoors = 2;
      availableWalls = 3;
      positionObjects();
      break;
    }
  case 5:
    {
      // cout<<"Creation of board of level 5\n\n";
      availableDiamonds = 8;
      availableMonsters = 5;
      availablePowerups = 4;
      availableDoors = 1;
      availableWalls = 5;
      positionObjects();
      break;
    }
  case 6:
    {
      // cout<<"Creation of board of level 6\n\n";
      availableDiamonds = 20;
      availableMonsters = 5;
      availablePowerups = 25;
      availableDoors = 2;
      availableWalls = 10;
      positionObjects();
      break;
    }
  default:
    {
      // User created board, values are the ones selected by user
      positionObjects();
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

int Board::getBoardLevel(){
  return level;
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

void Board::virusMonsters(int emptyRows, int emptyCols){
  int row = 0;
  int column = 0;
  int reproductionRate = 3;
  char c;
  // if (!virusModeBoard) {
  //   clearMonsters();
  // }
  for (int i = 0; i < reproductionRate; i++) {
    c = matrix[row][column].getSymbol();
    while ( c == 'X' or c == '*' or c == '$' or c == 'M' or c == '#' or c == '+') {
      row = rand() %emptyRows + 1;
      column = rand() %emptyCols + 1;
      c = matrix[row][column].getSymbol();
    }
    matrix[row][column].updateElement(row,column,"monster",'M');
  }
}

void Board::moveMonsters(){
  int rowPosition;
  int colPosition;
  int direction = 0;
  bool moveValid;
  char nextCh;

  for (size_t i = 0; i < monsters.size(); i++) {
    rowPosition = monsters[i].getMonsterX();
    colPosition = monsters[i].getMonsterY();
    matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"space",' ');
    moveValid = false;
    while (!moveValid) {
      rowPosition = monsters[i].getMonsterX();
      colPosition = monsters[i].getMonsterY();
      direction = rand() %4 + 1;
      switch (direction) {
        case 1:{
          rowPosition--;
          // cout<<"MOVING UP"<<endl;
          break;
        }
        case 2:{
          rowPosition++;
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
      }
      // Validation if movement is possible
      nextCh = matrix[rowPosition][colPosition].getSymbol();
      if (nextCh != 'X' and nextCh != '*' and nextCh != '$' and nextCh != '#' and nextCh != '+') {
        moveValid = true;
      }
    }
    monsters[i].updateMonsterCoords(rowPosition,colPosition);
    matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"monster",'M');
  }
}

string Board::play(Player &player){
  string move = "";
  const char *charedPlayerName = player.getName().c_str();
  // Initial player position which probably should be changed to a randomized pos
  int rowPosition;
  int colPosition;
  char userInput;
  int maxcols = COLS-1;

  colOrigin = maxcols/2-m;

  // Square area in which the player can teleport to
  int emptyRows = n-2;
  int emptyCols = m-2;

  // Initial random position of player in board
  int playerRow0 = rand() %emptyRows + 1;
  int playerCol0 = rand() %emptyCols + 1;

  while (matrix[playerCol0][playerRow0].getSymbol() != ' ') {
    playerRow0 = rand() %emptyRows + 1;
    playerCol0 = rand() %emptyCols + 1;
  }
  rowPosition = playerRow0;
  colPosition = playerCol0;
  matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player",'O');

  //Clear the contents of the previous window but maintaining the header info
  mvaddstr(4,0,"");
  clrtobot();

  displayBoard();
  mvprintw(rowOrigin+4, maxcols/2+infoBoxIdent, "PLAYER  %s ",charedPlayerName);
  mvprintw(rowOrigin+5, maxcols/2+infoBoxIdent, "($) Diamonds:  %d", player.Diamonds());
  mvprintw(rowOrigin+6, maxcols/2+infoBoxIdent, "(*) Powerups:  %d", player.Powerups());
  mvprintw(rowOrigin+7, maxcols/2+infoBoxIdent, "(O) Lives:     %d", player.Lives());

  mvaddstr(rowOrigin+9, maxcols/2+infoBoxIdent, "KEYBOARD MOVEMENT COMMANDS");
  mvaddstr(rowOrigin+10, maxcols/2+infoBoxIdent, "Press W A S D or ARROW KEYS for linear movement");
  mvaddstr(rowOrigin+11, maxcols/2+infoBoxIdent, "Press Q E Z C for diagonal movement");
  mvaddstr(rowOrigin+12, maxcols/2+infoBoxIdent, "SPECIAL KEYBORD COMMANDS");
  mvaddstr(rowOrigin+13, maxcols/2+infoBoxIdent, "Press T to teleport using 1 powerup (*)");
  mvaddstr(rowOrigin+14, maxcols/2+infoBoxIdent, "Press L to buy a life for 3 diamonds ($)");
  mvaddstr(rowOrigin+15, maxcols/2+infoBoxIdent, "Press N to skip board using 5 powerups (*)");
  mvaddstr(rowOrigin+16, maxcols/2+infoBoxIdent, "Press V to toogle Virus Mode");
  mvaddstr(rowOrigin+17, maxcols/2+infoBoxIdent, "Press K to terminate the game");
  mvaddstr(rowOrigin+18, maxcols/2+infoBoxIdent, "Press H to toogle help info");

  mvaddstr(rowOrigin, maxcols/2+infoBoxIdent, "ENTER NEXT MOVE: ");
  while (move != "STOP") {
    bool movementValid = 0;
    bool nextBoard = 0;
    if (player.Lives() > 0) {
      userInput = getch();
      mvprintw(rowOrigin, maxcols/2+infoBoxIdent,"");
      clrtoeol();
      mvprintw(rowOrigin, maxcols/2+infoBoxIdent, "ENTER NEXT MOVE: %c", userInput);
      mvprintw(rowOrigin+2, maxcols/2+infoBoxIdent,"");
      clrtoeol();
      refresh();

      if (virusModeBoard) {
        virusMonsters(emptyRows, emptyCols);
      }
      else {
        moveMonsters();
      }
      matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"space",'.');

      if (userInput == 'k' or userInput == 'K'){
        mvprintw(rowOrigin, maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvprintw(rowOrigin, maxcols/2+infoBoxIdent, "GAME OVER!");
        refresh();
        return "KILL";
      }

      else if (userInput == 'w' or userInput == 'A'){
        char nextStr = matrix[rowPosition-1][colPosition].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 1);
      }

      else if (userInput == 's' or userInput == 'B'){
        char nextStr = matrix[rowPosition+1][colPosition].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 2);
      }

      else if (userInput == 'd' or userInput == 'C'){
        char nextStr = matrix[rowPosition][colPosition+1].getSymbol();
        validateMovement(rowPosition, colPosition, nextStr, movementValid,
          nextBoard, player, 3);
      }

      else if (userInput == 'a' or userInput == 'D'){
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

      else if (userInput == 'c'){
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
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "YOU DO NOT HAVE ANY TELEPORTERS MATE!");
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
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "NOT ENOUGH POWER TO SKIP BOARD!");
        }
      }

      else if (userInput == 'l' or userInput == 'L'){
        if (player.Diamonds() >= 3) {
          movementValid = 1;
          player.incrementLives();
          for (size_t i = 0; i < 3; i++) {
            player.decrementDiamonds();
          }
        }
        else{
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "NOT ENOUGH DIAMONDS TO BUY A LIFE");
        }
      }

      else if (userInput == 'v' or userInput == 'V'){
        if (level != 6) {
          switchVirusMode();
          if (virusModeBoard) {
            mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "VIRUS MODE ACTIVATED");
          }
          else{
            mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "VIRUS MODE DISABLED");
          }
        }
        else {
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "VIRUS MODE CAN'T BE DISABLED IN THIS LEVEL");
        }
      }

      else if (userInput == 'h' or userInput == 'H'){
        int helpRow0 = 27;
        if (!helpShown) {
          help(helpRow0);
          helpShown = true;
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "HELP TOGGLED ON");
        }
        else {
          mvaddstr(rowOrigin+2, maxcols/2+infoBoxIdent, "HELP TOGGLED OFF");
          mvaddstr(helpRow0,0,"");
          clrtobot();
          helpShown = false;
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
        // This is to make sure the correct amount of items is shown to player
        mvaddstr(rowOrigin+5,maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvaddstr(rowOrigin+6,maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvaddstr(rowOrigin+7,maxcols/2+infoBoxIdent,"");
        clrtoeol();
        mvprintw(rowOrigin+5, maxcols/2+infoBoxIdent, "($) Diamonds:  %d", player.Diamonds());
        mvprintw(rowOrigin+6, maxcols/2+infoBoxIdent, "(*) Powerups:  %d", player.Powerups());
        mvprintw(rowOrigin+7, maxcols/2+infoBoxIdent, "(O) Lives:     %d", player.Lives());
      }
    }

    else{
      return "KILL";
    }
  }
  return "CONTINUE";
}

void Board::creator(){
  srand (time(NULL));
  char inputFilename[100];
  char inputAttribute[100];

  int maxcols, maxlines;
  int requestedBoards;
  int maxElementsAllowed = 30;

  string path = "../boards/user/";
  string ext = ".board";
  string filename;

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
  mvaddstr(0, maxcols/2-18, "<| STARK INDUSTRIES BOARD CREATOR v1.0 |>");
  mvaddstr(1, maxcols/2-16, "ALEXANDER MORAKHOVSKI | JULIAN LECHUGA");
  mvaddstr(3, maxcols/2-30, "Welcome! This is the board creator for ULTRON'S board game system!");
  helpCreator(4);
  mvaddstr(LINES-1, 0, "PRESS ANY KEY TO CONTINUE...");
  refresh();
  getch();
  mvaddstr(2,0,"");
  clrtobot();

  // User input of number of boards to create
  mvaddstr(3, 0, "Please enter the number of boards you would like to create: ");
  refresh();
  getstr(inputAttribute);
  requestedBoards = validateInputValue(3, inputAttribute, 1, 10);
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
    availableDiamonds = validateInputValue(5, inputAttribute, 1, maxElementsAllowed);
    mvaddstr(5,0,"");
    clrtoeol();
    mvprintw(5, 0, "Number of diamonds: %d", availableDiamonds);

    // User input of number of Monsters for board
    mvaddstr(7, 0, "Please enter the number of monsters: ");
    refresh();
    getstr(inputAttribute);
    availableMonsters = validateInputValue(7, inputAttribute, 1, maxElementsAllowed);
    mvaddstr(7,0,"");
    clrtoeol();
    mvprintw(7, 0, "Number of monsters: %d", availableMonsters);

    // User input of number of Powerups for board
    mvaddstr(9, 0, "Please enter the number of powerups: ");
    refresh();
    getstr(inputAttribute);
    availablePowerups = validateInputValue(9, inputAttribute, 1, maxElementsAllowed);
    mvaddstr(9,0,"");
    clrtoeol();
    mvprintw(9, 0, "Number of powerups: %d", availablePowerups);

    // User input of number of Powerups for board
    mvaddstr(11, 0, "Please enter the number of doors: ");
    refresh();
    getstr(inputAttribute);
    availableDoors = validateInputValue(11, inputAttribute, 1, maxElementsAllowed);
    mvaddstr(11,0,"");
    clrtoeol();
    mvprintw(11, 0, "Number of doors: %d", availableDoors);

    // User input of number of Powerups for board
    mvaddstr(13, 0, "Please enter the number of walls: ");
    refresh();
    getstr(inputAttribute);
    availableWalls = validateInputValue(13, inputAttribute, 1, maxElementsAllowed);
    mvaddstr(13,0,"");
    clrtoeol();
    mvprintw(13, 0, "Number of walls: %d", availableWalls);

    mvaddstr(maxlines, 0, "PRESS ANY KEY TO CREATE THE BOARD... ");
    getch();

    createTheMatrix(0, path + filename + ext);

    mvaddstr(3,0,"");
    clrtobot();
    mvprintw(3, 0, "Game board: %s.board", inputFilename);

    displayBoard();
    mvaddstr(maxlines, 0, "PRESS ANY KEY TO CONTINUE... ");
    refresh();
    getch();
  }

  mvaddstr(maxlines, 0, "YOU HAVE FINISHED ALL BOARDS, PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
}

Board::~Board(){
  // cout<<"Board "<<identifier<<" destroyed."<<"\n";
}
