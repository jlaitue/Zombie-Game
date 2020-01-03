#include "../inc/Board.hpp"
#include "../inc/Element.hpp"
#include "../inc/Player.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

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

// void Board::positionObjects(int nDiam, int nMons, int nDoors, int nStars, int nWalls){
//   srand (time(NULL));
//
//   while(nWalls != 0){
//       string direction = columnOrientation();
//       string s = "X";
//       int x1 = rand() %18 + 1;
//       int y1 = rand() %38 + 1;
//
//       // cout<<"Column orientation: "<<direction<<"\n";
//
//       //If beginning point is empty proceed
//       if(matrix[x1][y1] == " "){
//         // cout<<"Wall number: "<<nWalls<<"\n";
//         // cout<<"Coords: "<<x1<<" "<<y1<<"\n";
//
//         if(direction == "vertical"){
//           int length = rand() %18 + 1;
//           // cout<<"Length: "<<length<<"\n\n";
//           for (int i = 0; i < length; i++) {
//             if (matrix[x1+i][y1] == " ") {
//               matrix[x1+i][y1] = s;
//             }
//             else break;
//           }
//           nWalls --;
//         }
//
//         else if(direction == "horizontal"){
//           int length = rand() %38 + 1;
//           // cout<<"Length: "<<length<<"\n\n";
//           for (int i = 0; i < length; i++) {
//             if (matrix[x1][y1+i] == " ") {
//               matrix[x1][y1+i] = s;
//             }
//             else break;
//           }
//           nWalls --;
//         }
//
//       }
//     }
//
//   while(nDiam != 0){
//     int row = rand() %19 + 1;
//     int column = rand() %39 + 1;
//     if(matrix[row][column] == " "){
//       matrix[row][column] = "$";
//       nDiam --;
//     }
//   }
//
//   while(nMons != 0){
//     int row = rand() %19 + 1;
//     int column = rand() %39 + 1;
//     if(matrix[row][column] == " "){
//       matrix[row][column] = "M";
//       nMons --;
//     }
//   }
//
//   while(nStars != 0){
//     int row = rand() %19 + 1;
//     int column = rand() %39 + 1;
//     if(matrix[row][column] == " "){
//       matrix[row][column] = "*";
//       nStars --;
//     }
//   }
//
//   while(nDoors != 0){
//     int doorCoordCase = rand() %4 + 1;
//     switch (doorCoordCase) {
//       case 1:{
//         int row = rand() %18 + 1;
//         int column = 0;
//         matrix[row][column] = "/";
//         break;
//       }
//       case 2:{
//         int row = 0;
//         int column = rand() %38 + 1;
//         matrix[row][column] = "/";
//         break;
//       }
//       case 3:{
//         int row = rand() %18 + 1;
//         int column = 39;
//         matrix[row][column] = "/";
//         break;
//       }
//       case 4:{
//         int row = 19;
//         int column = rand() %38 + 1;
//         matrix[row][column] = "/";
//         break;
//       }
//     }
//     nDoors--;
//   }
// }

void Board::displayBoard(){
  for (int i = 0; i < n; i++) {
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

// void Board::createTheMatrix(int l, string filename){
//   level = l;
//   ofstream myfile ("../boards/" + filename);
//
// // Creation of string matrix with elements of board
//   for (int i = 0; i < n; i++) {
//       for (int j = 0; j < m; j++) {
//         //Creation of horizontal outer walls
//         if(i==0 or i == n-1){
//           matrix[i][j] = "X";
//         }
//         //Creation of vertical outer walls
//         else if(i > 0 and (j == 0 or j == m-1)){
//           matrix[i][j] = "X";
//         }
//         else if(i > 0 and (j > 0 and j < m-1)){
//           matrix[i][j] = " ";
//         }
//       }
//     }
//
// /*
// Positioning of different amount of elements depending on difficulty level
// chosen
// */
// switch (level) {
//   case 1:
//     {
//       cout<<"Creation of board of level 1\n\n";
//       int nDiam = 5, nMons = 1, nStars = 0, nDoors = 5, nWalls = 2;
//       positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
//       break;
//     }
//   case 2:
//     {
//       cout<<"Creation of board of level 2\n\n";
//       int nDiam = 5, nMons = 1, nStars = 1, nDoors = 4, nWalls = 2;
//       positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
//       break;
//     }
//   case 3:
//     {
//       cout<<"Creation of board of level 3\n\n";
//       int nDiam = 4, nMons = 3, nStars = 2, nDoors = 3, nWalls = 3;
//       positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
//       break;
//     }
//   case 4:
//     {
//       cout<<"Creation of board of level 4\n\n";
//       int nDiam = 4, nMons = 4, nStars = 3, nDoors = 2, nWalls = 3;
//       positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
//       break;
//     }
//   case 5:
//     {
//       cout<<"Creation of board of level 5\n\n";
//       int nDiam = 8, nMons = 5, nStars = 4, nDoors = 1, nWalls = 5;
//       positionObjects(nDiam, nMons, nDoors, nStars, nWalls);
//       break;
//     }
//
// }
//
//   // displayBoard();
//
// // Writting of matrix previously created to .txt file
//   if (myfile.is_open())
//   {
//     cout<<"Writting to board file: boards/"<< filename<<" ..."<<"\n";
//     for (int i = 0; i < n; i++) {
//       for (int j = 0; j < m; j++) {
//         myfile<<matrix[i][j];
//       }
//       myfile<<"\n";
//     }
//     myfile.close();
//     cout<<"Done writting."<<"\n";
//   }
//   else cout << "Unable to open file";
// }

void Board::getBoardLevel(){
  cout<<"Board with id "<<identifier<<" has level: "<<level<<"\n";
}

//THIS FUNCTION WILL GO TO THE "GAME" CLASS
void Board::play(){
  string move = "";
  int rowPosition = n/2;
  int colPosition = m/2;
  int cDiams = 0, cStars = 0, lives = 3;

  matrix[rowPosition][colPosition].updateElement(rowPosition,colPosition,"player","O");
  cout<<"Initial position (x,y) =  "<<rowPosition<<", "<<colPosition<<endl;
  cout<<"Initialized matrix: \n\n";
  displayBoard();

  while (move != "STOP") {
    bool movementValid = 0;
    cout<<"\nEnter move: ";
    cin>>move;
    matrix[rowPosition][colPosition].updateSymbol(".");

    if (move == "w" or move == "W"){
      string nextStr = matrix[rowPosition-1][colPosition].getSymbol();
      // int moveCase = 1;
      // updateCounters(movementValid, rowPosition, moveCase, nextStr, cDiams, cStars, lives);
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        rowPosition --;
        cout<<"Moving UP"<<endl;
        movementValid = 1;
      }
    }

    if (move == "s" or move == "S"){
      string nextStr = matrix[rowPosition+1][colPosition].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        rowPosition ++;
        cout<<"Moving DOWN"<<endl;
        movementValid = 1;
      }
    }

    if (move == "d" or move == "D"){
      string nextStr = matrix[rowPosition][colPosition+1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition++;
        cout<<"Moving RIGHT"<<endl;
        movementValid = 1;
      }
    }

    if (move == "a" or move == "A"){
      string nextStr = matrix[rowPosition][colPosition-1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition--;
        cout<<"Moving LEFT"<<endl;
        movementValid = 1;
      }
    }

    if (move == "e" or move == "E"){
      string nextStr = matrix[rowPosition-1][colPosition+1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition++;
        rowPosition--;
        cout<<"Moving DIAGONALLY UP R "<<endl;
        movementValid = 1;
      }
    }

    if (move == "q" or move == "Q"){
      string nextStr = matrix[rowPosition-1][colPosition-1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition--;
        rowPosition--;
        cout<<"Moving DIAGONALLY UP L "<<endl;
        movementValid = 1;
      }
    }

    if (move == "z" or move == "Z"){
      string nextStr = matrix[rowPosition+1][colPosition-1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition--;
        rowPosition++;
        cout<<"Moving DIAGONALLY DOWN L"<<endl;
        movementValid = 1;
      }
    }

    if (move == "c" or move == "C"){
      string nextStr = matrix[rowPosition+1][colPosition+1].getSymbol();
      if (nextStr == "X") {
        cout<<"Invalid move. There is an obstacle.\n";
      }
      else{
        if(nextStr == "$"){
          cDiams++;
        }
        else if(nextStr == "*"){
          cStars++;
        }
        else if(nextStr == "M"){
          lives--;
        }
        colPosition++;
        rowPosition++;
        cout<<"Moving DIAGONALLY DOWN R"<<endl;
        movementValid = 1;
      }
    }

    if (move == "p" or move == "P"){
      movementValid = 1;
      if (cStars > 0) {
        int row = 0;
        int column = 0;

        while (matrix[row][column].getSymbol() == "X") {
          row = rand() %18 + 1;
          column = rand() %38 + 1;
        }
        cStars--;
        rowPosition = row;
        colPosition = column;
      }
      else{
        cout<<"You do not have any teleporters. Sorry!"<<endl;
      }
    }

    if (move == "x" or move == "X"){
      cout<<"Game terminated.\n";
      cout<<"Final score: "<<cDiams<<" diamonds collected."<<endl;
      move = "STOP";
    }

    matrix[rowPosition][colPosition].updateSymbol("O");
    if (movementValid) {
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard();
      cout<<"Player has: "<<cDiams<<" diamonds.\n";
      cout<<"Player has: "<<cStars<<" stars.\n";
      cout<<"Player has: "<<lives<<" lives.\n";
    }
  }
}

Board::~Board(){
  cout<<"Board "<<identifier<<" destroyed."<<"\n";
}
