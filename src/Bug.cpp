  #include <iostream>
  #include <string>
  #include <fstream>
  #include <ctime>
  #include <sstream>
  using namespace std;

  // if (nextStr == "X") {
  //   cout<<"Invalid move. There is an obstacle.\n";
  // }
  // else{
  //   movementValid = 1;
  //   if(nextStr == "$"){
  //     cDiams++;
  //   }
  //   else if(nextStr == "*"){
  //     cStars++;
  //   }
  //   else if(nextStr == "M"){
  //     lives--;
  //   }
  // }
  int main() {

    //This code is a try to clean the method for createTheMatrix()
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

    //Code for creating several random boards and integer parsing
    // for (size_t i = 0; i < 20; i++) {
      //   int level = rand() %5 + 1;
      //   stringstream ss;
      //   ss<<i;
      //   string s;
      //   ss>>s;
      //   createTheMatrix(level, s+"prueba.txt");
      // }
      // void play(){
      //   string move = "";
      //   int rowPosition = n/2;
      //   int colPosition = m/2;
      //   int cDiams = 0, cStars = 0, lives = 3;
      //
      //   while (move != "STOP") {
      //     bool movementValid = 0;
      //     cout<<"\nENTER NEXT MOVE: ";
      //     cin>>move;
      //     matrix[rowPosition][colPosition].updateSymbol(".");
      //
      //     if (move == "w" or move == "W"){
      //       string nextStr = matrix[rowPosition-1][colPosition].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         rowPosition --;
      //         cout<<"MOVING UP"<<endl;
      //       }
      //     }
      //
      //     if (move == "s" or move == "S"){
      //       string nextStr = matrix[rowPosition+1][colPosition].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         rowPosition ++;
      //         cout<<"MOVING DOWN"<<endl;
      //       }
      //     }
      //
      //     else if (move == "d" or move == "D"){
      //       string nextStr = matrix[rowPosition][colPosition+1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition++;
      //         cout<<"MOVING RIGHT"<<endl;
      //       }
      //     }
      //
      //     else if (move == "a" or move == "A"){
      //       string nextStr = matrix[rowPosition][colPosition-1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition--;
      //         cout<<"MOVING LEFT"<<endl;
      //       }
      //     }
      //
      //     else if (move == "e" or move == "E"){
      //       string nextStr = matrix[rowPosition-1][colPosition+1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition++;
      //         rowPosition--;
      //         cout<<"MOVING DIAGONALLY UP R "<<endl;
      //       }
      //     }
      //
      //     else if (move == "q" or move == "Q"){
      //       string nextStr = matrix[rowPosition-1][colPosition-1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition--;
      //         rowPosition--;
      //         cout<<"MOVING DIAGONALLY UP L "<<endl;
      //       }
      //     }
      //
      //     else if (move == "z" or move == "Z"){
      //       string nextStr = matrix[rowPosition+1][colPosition-1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition--;
      //         rowPosition++;
      //         cout<<"MOVING DIAGONALLY DOWN L"<<endl;
      //       }
      //     }
      //
      //     else if (move == "c" or move == "C"){
      //       string nextStr = matrix[rowPosition+1][colPosition+1].getSymbol();
      //       validateMovement(nextStr);
      //       if (movementValid) {
      //         colPosition++;
      //         rowPosition++;
      //         cout<<"MOVING DIAGONALLY DOWN R"<<endl;
      //       }
      //     }
      //
      //     else if (move == "p" or move == "P"){
      //       movementValid = 1;
      //       if (cStars > 0) {
      //         int row = 0;
      //         int column = 0;
      //
      //         //Maybe add rule that forbids teleportation to the place of a Monster
      //         while (matrix[row][column].getSymbol() == "X") {
      //           row = rand() %emptyRows + 1;
      //           column = rand() %emptyCols + 1;
      //         }
      //         cStars--;
      //         rowPosition = row;
      //         colPosition = column;
      //       }
      //       else{
      //         cout<<"You do not have any teleporters. Sorry!"<<endl;
      //       }
      //     }
      //
      //     else if (move == "x" or move == "X"){
      //       cout<<"GAME TERMINATED.\n";
      //       cout<<"FINAL SCORE: "<<cDiams<<" diamonds collected."<<endl;
      //       move = "STOP";
      //     }
      //     else{
      //       cout<<"Try a valid key input.\n";
      //     }
      //
      //     matrix[rowPosition][colPosition].updateSymbol("O");
      //     if (movementValid) {
      //       cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      //       displayBoard();
      //       cout<<"Player has: "<<cDiams<<" diamonds.\n";
      //       cout<<"Player has: "<<cStars<<" stars.\n";
      //       cout<<"Player has: "<<lives<<" lives.\n";
      //     }
      //   }
      // }


    return 0;
  }
