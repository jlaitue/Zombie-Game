#include "../inc/Board.hpp"
#include "../inc/Element.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

int Board::boardCount = 0;

Board::Board(){
  cout<<"Board created"<<endl;
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
  srand (time(NULL));
  int emptyRows = n-2;
  int emptyCols = m-2;
  while(nWalls != 0){
      string direction = columnOrientation();
      string s = "X";
      int x1 = rand() %emptyRows + 1;
      int y1 = rand() %emptyCols + 1;

      // cout<<"Column orientation: "<<direction<<"\n";

      //If beginning point is empty proceed
      if(matrix[x1][y1].getSymbol() == " "){
        // cout<<"Wall number: "<<nWalls<<"\n";
        // cout<<"Coords: "<<x1<<" "<<y1<<"\n";

        if(direction == "vertical"){
          int length = rand() %emptyRows + 1;
          // cout<<"Length: "<<length<<"\n\n";
          for (int i = 0; i < length; i++) {
            if (matrix[x1+i][y1].getSymbol() == " ") {
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
            if (matrix[x1][y1+i].getSymbol() == " ") {
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
    if(matrix[row][column].getSymbol() == " "){
      matrix[row][column].updateElement(row,column,"diamond","$");
      nDiam --;
    }
  }

  while(nMons != 0){
    int row = rand() %emptyRows + 1;
    int column = rand() %emptyCols + 1;
    if(matrix[row][column].getSymbol() == " "){
      matrix[row][column].updateElement(row,column,"monster","M");
      nMons --;
    }
  }

  while(nStars != 0){
    int row = rand() %emptyRows + 1;
    int column = rand() %emptyCols + 1;
    if(matrix[row][column].getSymbol() == " "){
      matrix[row][column].updateElement(row,column,"power","*");
      nStars --;
    }
  }

  while(nDoors != 0){
    int doorCoordCase = rand() %4 + 1;
    switch (doorCoordCase) {
      case 1:{
        int row = rand() %emptyRows + 1;
        int column = 0;
        matrix[row][column].updateElement(row,column,"door","/");
        break;
      }
      case 2:{
        int row = 0;
        int column = rand() %emptyCols + 1;
        matrix[row][column].updateElement(row,column,"door","/");
        break;
      }
      case 3:{
        int row = rand() %emptyRows + 1;
        int column = 39;
        matrix[row][column].updateElement(row,column,"door","/");
        break;
      }
      case 4:{
        int row = 19;
        int column = rand() %emptyCols + 1;
        matrix[row][column].updateElement(row,column,"door","/");
        break;
      }
    }
    nDoors--;
  }
}

void Board::displayBoard(){
  //Small code for centering the board in terminal
  string centeringSpace = "";
  for (int k = 0; k < 26; k++){
    centeringSpace = centeringSpace + " ";
  }
  //Display of gameboard
  for (int i = 0; i < n; i++) {
    cout<<centeringSpace;
    if(i<10){cout<<i<<"  ";}
    else{cout<<i<<" ";}
    for (int j = 0; j < m; j++) {
      // if (i == n-1) {cout<<j;}
      cout<<matrix[i][j].getSymbol();
    }
    cout<<"\n";
  }
  cout<<"\n";
}

void Board::readBoard(string filename){
  cout<<"Operation READING..."<<"\n";
  string line;
  int rows=0,columns=0;
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0, doorscount = 0;

  fstream inFile;
  inFile.open("../boards/"+filename);

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }
  cout << "Reading board file: "<<filename<<"\n\n";
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
            matrix[rows][i].updateElement(rows,i,"wall","X");
            xcount ++;
          }
          else if (line[i] == '*'){
            // cout<<"FOUND A POWERUP ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"power","*");
            powcount++;
          }
          else if (line[i] == '$'){
            // cout<<"FOUND A DIAMOND ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"diam","$");
            diamcount++;

          }
          else if (line[i] == 'M'){
            // cout<<"FOUND A MONSTER ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"mons","M");
            monscount++;
          }
          else if (line[i] == ' '){
            // cout<<"FOUND EMPTY SPACE ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"space"," ");
            whitecount++;
          }
          else if (line[i] == 'J'){
            // cout<<"FOUND PLAYER ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            Player player1(1,rows,i,"player","J");
            matrix[rows][i] = player1;
          }
          else if (line[i] == '/'){
            // cout<<"FOUND DOOR ";
            // cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i].updateElement(rows,i,"door","/");
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
    columns = m;
    cout<<"Total Rows: "<<rows<<"\n";
    cout<<"Total Columns: "<<columns<<"\n";
    cout<<"\n\n";
}

void Board::createTheMatrix(int l, string filename){
  level = l;
  ofstream myfile ("../boards/" + filename);

// Creation of string matrix with elements of board
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        //Creation of horizontal outer walls
        if(i==0 or i == n-1){
          matrix[i][j].updateElement(i,j,"wall","X");
        }
        //Creation of vertical outer walls
        else if(i > 0 and (j == 0 or j == m-1)){
          matrix[i][j].updateElement(i,j,"wall","X");
        }
        else if(i > 0 and (j > 0 and j < m-1)){
          matrix[i][j].updateElement(i,j,"space"," ");
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
      cout<<"Creation of board of level 1\n\n";
      int nDiam = 5, nMons = 1, nStars = 0, nDoors = 5, nWalls = 2;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 2:
    {
      cout<<"Creation of board of level 2\n\n";
      int nDiam = 5, nMons = 1, nStars = 1, nDoors = 4, nWalls = 2;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 3:
    {
      cout<<"Creation of board of level 3\n\n";
      int nDiam = 4, nMons = 3, nStars = 2, nDoors = 3, nWalls = 3;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 4:
    {
      cout<<"Creation of board of level 4\n\n";
      int nDiam = 4, nMons = 4, nStars = 3, nDoors = 2, nWalls = 3;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }
  case 5:
    {
      cout<<"Creation of board of level 5\n\n";
      int nDiam = 8, nMons = 5, nStars = 4, nDoors = 1, nWalls = 5;
      positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
      break;
    }

}
  // displayBoard();

// Writting of matrix previously created to .txt file
  if (myfile.is_open())
  {
    cout<<"Writting to board file: boards/"<< filename<<" ..."<<"\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        myfile<<matrix[i][j].getSymbol();
      }
      myfile<<"\n";
    }
    myfile.close();
    cout<<"Done writting."<<"\n";
  }
  else cout << "Unable to open file";
}

void Board::getBoardLevel(){
  cout<<"Board with id "<<identifier<<" has level: "<<level<<"\n";
}

void validateMovement(int &rowPosition, int &colPosition, string nextStr,
  bool &movementValid, int &cDiams,
  int &cStars, int &lives, int moveCase){

  if (nextStr == "X") {
    cout<<"Invalid move. There is an obstacle.\n";
  }
  else{
    movementValid = 1;
    if(nextStr == "$"){
      cDiams++;
    }
    else if(nextStr == "*"){
      cStars++;
    }
    else if(nextStr == "M"){
      lives--;
    }
    switch (moveCase) {
      case 1:{
        rowPosition --;
        cout<<"MOVING UP"<<endl;
        break;
      }
      case 2:{
        rowPosition ++;
        cout<<"MOVING DOWN"<<endl;
        break;
      }
      case 3:{
        colPosition++;
        cout<<"MOVING RIGHT"<<endl;
        break;
      }
      case 4:{
        colPosition--;
        cout<<"MOVING LEFT"<<endl;
        break;
      }
      case 5:{
        colPosition++;
        rowPosition--;
        cout<<"MOVING DIAGONALLY UP R "<<endl;
        break;
      }
      case 6:{
        colPosition--;
        rowPosition--;
        cout<<"MOVING DIAGONALLY UP L "<<endl;
        break;
      }
      case 7:{
        colPosition--;
        rowPosition++;
        cout<<"MOVING DIAGONALLY DOWN L"<<endl;
        break;
      }
      case 8:{
        colPosition++;
        rowPosition++;
        cout<<"MOVING DIAGONALLY DOWN R"<<endl;
        break;
      }
    }

  }
}

void Board::play(){
  string move = "";
  int rowPosition = n/2;
  int colPosition = m/2;
  int cDiams = 0, cStars = 0, lives = 3;
  int emptyRows = n-2;
  int emptyCols = m-2;

  matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player","O");
  cout<<"Initial player position (x,y) =  "<<rowPosition<<", "<<colPosition<<endl;
  cout<<"Initialized BOARD: \n\n";
  displayBoard();

  while (move != "STOP") {
    bool movementValid = 0;
    cout<<"\nENTER NEXT MOVE: ";
    cin>>move;

    matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"space",".");

    if (move == "w" or move == "W"){
      string nextStr = matrix[rowPosition-1][colPosition].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 1);
    }

    else if (move == "s" or move == "S"){
      string nextStr = matrix[rowPosition+1][colPosition].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 2);
    }

    else if (move == "d" or move == "D"){
      string nextStr = matrix[rowPosition][colPosition+1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 3);
    }

    else if (move == "a" or move == "A"){
      string nextStr = matrix[rowPosition][colPosition-1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 4);
    }

    else if (move == "e" or move == "E"){
      string nextStr = matrix[rowPosition-1][colPosition+1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 5);
    }

    else if (move == "q" or move == "Q"){
      string nextStr = matrix[rowPosition-1][colPosition-1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 6);
    }

    else if (move == "z" or move == "Z"){
      string nextStr = matrix[rowPosition+1][colPosition-1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 7);
    }

    else if (move == "c" or move == "C"){
      string nextStr = matrix[rowPosition+1][colPosition+1].getSymbol();
      validateMovement(rowPosition, colPosition, nextStr, movementValid, cDiams,
         cStars, lives, 8);
    }

    else if (move == "p" or move == "P"){
      movementValid = 1;
      if (cStars > 0) {
        int row = 0;
        int column = 0;

        //Maybe add rule that forbids teleportation to the place of a Monster
        while (matrix[row][column].getSymbol() == "X") {
          row = rand() %emptyRows + 1;
          column = rand() %emptyCols + 1;
        }
        cStars--;
        rowPosition = row;
        colPosition = column;
      }
      else{
        cout<<"You do not have any teleporters. Sorry!"<<endl;
      }
    }

    else if (move == "k" or move == "K"){
      cout<<"GAME TERMINATED.\n";
      cout<<"FINAL SCORE: "<<cDiams<<" diamonds collected."<<endl;
      move = "STOP";
    }

    else{
      cout<<"TRY A VALID KEY INPUT.\n";
    }

    if (movementValid) {
      matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player","O");
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard();
      cout<<"PLAYER HUD\n";
      cout<<"DIAMONDS: "<<cDiams<<endl;
      cout<<"POWERUPS: "<<cStars<<endl;
      cout<<"LIVES   : "<<lives<<endl;
    }
  }
}

Board::~Board(){
  // cout<<"Board "<<identifier<<" destroyed."<<"\n";
}
