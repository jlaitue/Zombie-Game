#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include "../inc/Element.hpp"
#include "../inc/Monster.hpp"
#include "../inc/Diamond.hpp"
#include "../inc/Door.hpp"
#include "../inc/Board.hpp"
using namespace std;

const size_t n = 20;
const size_t m = 40;

void displayBoard(string matrix[][m], size_t n, size_t m){
    for (size_t i = 0; i < n; i++) {
      if(i<10){cout<<i<<"  ";}
      else{cout<<i<<" ";}
      for (size_t j = 0; j < m; j++) {
        // if (i == n-1) {cout<<j;}
        cout<<matrix[i][j];
      }
      cout<<"\n";
    }
    cout<<"\n";
  }

// void updateCounters(bool movementValid, int rowPosition, int moveCase, string nextStr, int cDiams, int cStars, int lives){
//   if (nextStr == "X") {
//     cout<<"Invalid move. There is an obstacle.\n";
//   }
//   else{
//     if(nextStr == "$"){
//       cDiams++;
//     }
//     else if(nextStr == "*"){
//       cStars++;
//     }
//     else if(nextStr == "M"){
//       lives--;
//     }
//     switch (moveCase) {
//       case 1:{
//         rowPosition --;
//         cout<<"Moving UP"<<endl;
//         movementValid = 1;
//       }
//     }
//   }
// }


//THIS FUNCTION WILL GO TO THE "GAME" CLASS
void movement(string matrix[][m], size_t n, size_t m){
  string move = "";
  int rowPosition = n/2;
  int colPosition = m/2;
  int cDiams = 0, cStars = 0, lives = 3;

  matrix[rowPosition][colPosition] = "O";
  cout<<"Intial position (x,y) =  "<<rowPosition<<", "<<colPosition<<endl;
  cout<<"Initialized matrix: \n\n";
  displayBoard(matrix,n,m);

  while (move != "STOP") {
    bool movementValid = 0;
    cout<<"\nEnter move: ";
    cin>>move;
    matrix[rowPosition][colPosition] = ".";

    if (move == "w" or move == "W"){
      string nextStr = matrix[rowPosition-1][colPosition];
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
      string nextStr = matrix[rowPosition+1][colPosition];
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
      string nextStr = matrix[rowPosition][colPosition+1];
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
      string nextStr = matrix[rowPosition][colPosition-1];
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
      string nextStr = matrix[rowPosition-1][colPosition+1];
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
      string nextStr = matrix[rowPosition-1][colPosition-1];
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
      string nextStr = matrix[rowPosition+1][colPosition-1];
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
      string nextStr = matrix[rowPosition+1][colPosition+1];
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

        while (matrix[row][column] == "X") {
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

    matrix[rowPosition][colPosition] = "O";
    if (movementValid) {
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
      cout<<"Player has: "<<cDiams<<" diamonds.\n";
      cout<<"Player has: "<<cStars<<" stars.\n";
      cout<<"Player has: "<<lives<<" lives.\n";
    }
  }
}

int main() {
  // string matrix[n][m];


  //Code for creating several random boards and integer parsing
  // for (size_t i = 0; i < 20; i++) {
  //   int level = rand() %5 + 1;
  //   stringstream ss;
  //   ss<<i;
  //   string s;
  //   ss>>s;
  //   createTheMatrix(level, s+"prueba.txt");
  // }


  int boardId = 1;
  // Element element;
  Board tablero(boardId);
  cout<<"Total number of elements created: "<<Element::objectCount<<endl;
  tablero.readBoard("0prueba.txt");
  tablero.displayBoard();
  // tablero.getBoardLevel();
  // tablero.createTheMatrix(3, "TEST.txt");
  // tablero.getBoardLevel();
  // tablero.displayBoard();
  cout<<"Total number of boards created: "<<Board::boardCount<<endl;
  cout<<"Total number of elements created: "<<Element::objectCount<<endl;
  cout<<"Total number of elements eliminated: "<<Element::deletedCount<<endl;


  // Monster monster1(1);
  // monster1.showElement();
  //
  // Diamond diamond(1,2,3);
  // diamond.showElement();
  //
  // Door door(2,3,4);
  // door.showElement();



  return 0;
}
