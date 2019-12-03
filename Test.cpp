#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include "Element.hpp"
#include "Monster.hpp"
using namespace std;

const size_t n = 6;
const size_t m = 15;

void getGridSize(int dimensions[2]){
  // array  dimensions;
  string line;
  int rows=0,columns=0;

  fstream inFile;
  inFile.open("tableau.txt");

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }

  while (getline(inFile, line)) {
    rows++;
    }
    columns = line.size();
    inFile.close();
    dimensions[0] = rows;
    dimensions[1] = columns;

    // return dimensions;
}

void printMatrix(string matrix[][m], size_t n, size_t m){
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      cout<<matrix[i][j]<<" ";
    }
    cout<<"\n";
  }
  cout<<"\n";
}

void movement(string matrix[][m], size_t n, size_t m){
  string move = "";
  int rowPosition = n/2;
  int colPosition = m/2;

  matrix[rowPosition][colPosition] = "O";
  cout<<"Intial position (x,y) =  "<<rowPosition<<", "<<colPosition<<endl;
  cout<<"Initialized matrix: \n\n";
  printMatrix(matrix,n,m);
  while (move != "STOP") {
    cout<<"\nEnter move: ";
    cin>>move;

    if (move == "w"){
      matrix[rowPosition][colPosition] = "X";
      rowPosition --;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving UP"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "s"){
      matrix[rowPosition][colPosition] = "X";
      rowPosition ++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving DOWN"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "d"){
      matrix[rowPosition][colPosition] = "X";
      colPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving RIGHT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "a"){
      matrix[rowPosition][colPosition] = "X";
      colPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving LEFT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "e"){
      matrix[rowPosition][colPosition] = "X";
      colPosition++;
      rowPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "q"){
      matrix[rowPosition][colPosition] = "X";
      colPosition--;
      rowPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "z"){
      matrix[rowPosition][colPosition] = "X";
      colPosition--;
      rowPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }

    if (move == "c"){
      matrix[rowPosition][colPosition] = "X";
      colPosition++;
      rowPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }
    if (move == "x"){
      move = "STOP";
    }
  }
}

void fileReading(string matrix[][m]){
  string line;
  int rows=0,columns=0;
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0;

  fstream inFile;
  inFile.open("tableau.txt");

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }

  while (getline(inFile, line)) {
        cout<<"Analyzing row: "<<rows<<endl;
        // using printf() in all tests for consistency
        // cout<<line;
        // cout<<line.size();
        for(size_t i = 0; i < line.length(); i++)
        {
          // cout<<"Fila "<<i<<endl;
          if (line[i] == 'X'){
            cout<<"FOUND AN X ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "X";
            xcount ++;
          }
          else if (line[i] == '*'){
            cout<<"FOUND A POWERUP ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "*";
            powcount++;
          }
          else if (line[i] == '$'){
            cout<<"FOUND A DIAMOND ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "$";
            diamcount++;

          }
          else if (line[i] == 'M'){
            cout<<"FOUND A MONSTER";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "M";
            monscount++;
          }
          else if (line[i] == ' '){
            cout<<"FOUND EMPTY SPACE";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = " ";
            whitecount++;
          }
          else if (line[i] == 'J'){
            cout<<"FOUND PLAYER ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "J";
          }
        }
        printf("\n");
        rows ++;
    }
    cout<<"Amount X "<<xcount<<endl;
    cout<<"Amount * "<<powcount<<endl;
    cout<<"Amount $ "<<diamcount<<endl;
    cout<<"Amount M "<<monscount<<endl;
    cout<<"Amount ' ' "<<whitecount<<endl;

    columns = line.size();
    cout<<"Total Rows: "<<rows<<endl;
    cout<<"Total Columns: "<<columns<<endl;
    cout<<"\n\n\n";
}

void createMatrix(){
  ofstream myfile ("EX1.txt");
  if (myfile.is_open())
  {
    for (size_t i = 0; i < 20; i++) {
      myfile << "XXXXXXXXXXXXXXXXXXXX\n";
    }
    myfile.close();
  }
  else cout << "Unable to open file";
}

int main() {
  string matrix[n][m];

  // for (size_t i = 0; i < n; i++) {
  //   for (size_t j = 0; j < m; j++) {
  //     matrix[i][j] = "X";
  //   }
  // }

  // Element element1("static", 0, 1, "$");
  // Element element2("static", 1, 1, "X");
  //
  // element1.showElement();
  // element2.showElement();

  // Monster monster1("Juan");
  // Monster monster2("Mike");
  //
  // monster1.showMonster();
  // monster2.showMonster();

  // fileReading(matrix);
  // printMatrix(matrix,n,m);
  // movement(matrix,n,m);

  // createMatrix();
  string cul = "HOLA";
  cout<<cul[1]<<endl;
  cul.replace(1,1,"X");
  cout<<cul<<endl;
  return 0;
}
