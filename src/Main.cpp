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
  Board tablero(boardId);
  cout<<"Total number of elements created: "<<Element::objectCount<<endl;
  // tablero.readBoard("0prueba.txt");
  tablero.createTheMatrix(4,"TRY.txt");
  tablero.displayBoard();
  // tablero.getBoardLevel();
  cout<<"Total number of boards created: "<<Board::boardCount<<endl;
  cout<<"Total number of elements created: "<<Element::objectCount<<"\n\n";
  // cout<<"Total number of elements eliminated: "<<Element::deletedCount<<endl;
  tablero.play();

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
