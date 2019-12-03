#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Element.hpp"
#include "Monster.hpp"
using namespace std;

const size_t n = 20;
const size_t m = 40;

void displayBoard(string matrix[][m], size_t n, size_t m){
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        cout<<matrix[i][j];
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
  displayBoard(matrix,n,m);
  while (move != "STOP") {
    cout<<"\nEnter move: ";
    cin>>move;

    if (move == "w" or move == "W"){
      matrix[rowPosition][colPosition] = ".";
      rowPosition --;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving UP"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "s" or move == "S"){
      matrix[rowPosition][colPosition] = ".";
      rowPosition ++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving DOWN"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "d" or move == "D"){
      matrix[rowPosition][colPosition] = ".";
      colPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving RIGHT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "a" or move == "A"){
      matrix[rowPosition][colPosition] = ".";
      colPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving LEFT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "e" or move == "E"){
      matrix[rowPosition][colPosition] = ".";
      colPosition++;
      rowPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "q" or move == "Q"){
      matrix[rowPosition][colPosition] = ".";
      colPosition--;
      rowPosition--;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "z" or move == "Z"){
      matrix[rowPosition][colPosition] = ".";
      colPosition--;
      rowPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }

    if (move == "c" or move == "C"){
      matrix[rowPosition][colPosition] = ".";
      colPosition++;
      rowPosition++;
      matrix[rowPosition][colPosition] = "O";
      cout<<"Moving "<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      displayBoard(matrix,n,m);
    }
    if (move == "x" or move == "X"){
      move = "STOP";
    }
  }
}

void boardReading(string filename, string matrix[][m]){
  string line;
  int rows=0,columns=0;
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0, doorscount = 0;

  fstream inFile;
  inFile.open(filename);

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }
  cout << "Reading board file: "<<filename<<"\n\n";
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
            cout<<"FOUND A MONSTER ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "M";
            monscount++;
          }
          else if (line[i] == ' '){
            cout<<"FOUND EMPTY SPACE ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = " ";
            whitecount++;
          }
          else if (line[i] == 'J'){
            cout<<"FOUND PLAYER ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "J";
          }
          else if (line[i] == '/'){
            cout<<"FOUND DOOR ";
            cout<<"Coordinates: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "/";
          }
        }
        cout<<"\n";
        rows ++;
    }
    cout<<"Amount X "<<xcount<<endl;
    cout<<"Amount * "<<powcount<<endl;
    cout<<"Amount $ "<<diamcount<<endl;
    cout<<"Amount M "<<monscount<<endl;
    cout<<"Amount / "<<doorscount<<endl;
    cout<<"Amount ' ' "<<whitecount<<endl;

    /* This value of columns is zero because when the .txt file is saved, a new
    line is added at the end. The files have 21 lines, being the last one empty
    which is why the value size of that last line is 0
    */
    // columns = line.size();
    columns = m;
    cout<<"Total Rows: "<<rows<<endl;
    cout<<"Total Columns: "<<columns<<endl;
    cout<<"\n\n\n";
}

void positionObjects(int nDiam, int nMons, int nDoors, int nStars, string matrix[][m]){
  srand (time(NULL));

  while(nDiam != 0){
    int row = rand() %19 + 1;
    int column = rand() %39 + 1;
    if(matrix[row][column] == " "){
      matrix[row][column] = "$";
      nDiam --;
    }
  }

  while(nMons != 0){
    int row = rand() %19 + 1;
    int column = rand() %39 + 1;
    if(matrix[row][column] == " "){
      matrix[row][column] = "M";
      nMons --;
    }
  }

  while(nStars != 0){
    int row = rand() %19 + 1;
    int column = rand() %39 + 1;
    if(matrix[row][column] == " "){
      matrix[row][column] = "*";
      nStars --;
    }
  }

  while(nDoors != 0){
    int doorCoordCase = rand() %4 + 1;
    switch (doorCoordCase) {
      case 1:{
        int row = rand() %18 + 1;
        int column = 0;
        matrix[row][column] = "/";
        break;
      }
      case 2:{
        int row = 0;
        int column = rand() %38 + 1;
        matrix[row][column] = "/";
        break;
      }
      case 3:{
        int row = rand() %18 + 1;
        int column = 39;
        matrix[row][column] = "/";
        break;
      }
      case 4:{
        int row = 19;
        int column = rand() %38 + 1;
        matrix[row][column] = "/";
        break;
      }
    }
    nDoors--;
  }
}

void createTheMatrix(int level, string filename){
  string matrix[n][m];
  ofstream myfile ("boards/"+ filename);

// Creation of string matrix with elements of board
  for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        if(i==0 or i == n-1){
          matrix[i][j] = "X";
        }
        else if(i > 0 and (j == 0 or j == m-1)){
          matrix[i][j] = "X";
        }
        else if(i > 0 and (j > 0 and j < m-1)){
          matrix[i][j] = " ";
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
      int nDiam = 5, nMons = 1, nStars = 0, nDoors = 5;
      positionObjects(nDiam, nMons, nDoors, nStars, matrix);
      break;
    }
  case 2:
    {
      cout<<"Creation of board of level 2\n\n";
      int nDiam = 5, nMons = 1, nStars = 1, nDoors = 4;
      positionObjects(nDiam, nMons, nDoors, nStars, matrix);
      break;
    }
  case 3:
    {
      cout<<"Creation of board of level 3\n\n";
      int nDiam = 4, nMons = 3, nStars = 2, nDoors = 3;
      positionObjects(nDiam, nMons, nDoors, nStars, matrix);
      break;
    }
  case 4:
    {
      cout<<"Creation of board of level 4\n\n";
      int nDiam = 4, nMons = 4, nStars = 3, nDoors = 2;
      positionObjects(nDiam, nMons, nDoors, nStars, matrix);
      break;
    }
  case 5:
    {
      cout<<"Creation of board of level 5\n\n";
      int nDiam = 8, nMons = 5, nStars = 4, nDoors = 1;
      positionObjects(nDiam, nMons, nDoors, nStars, matrix);
      break;
    }
}

  displayBoard(matrix, n, m);

// Writting of matrix previously created to .txt file
  if (myfile.is_open())
  {
    cout<<"Writting to board file: boards/"<< filename<<" ..."<<endl;
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        myfile<<matrix[i][j];
      }
      myfile<<"\n";
    }
    myfile.close();
    cout<<"Done writting."<<endl;
  }
  else cout << "Unable to open file";
}

int main() {
  string matrix[n][m];
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


  // createTheMatrix(1, "prueba1.txt");
  // createTheMatrix(2, "prueba2.txt");
  // createTheMatrix(3, "prueba3.txt");
  // createTheMatrix(4, "prueba4.txt");
  // createTheMatrix(5, "prueba5.txt");
  createTheMatrix(3, "prueba6.txt");
  // boardReading("boards/prueba1.txt", matrix);
  // displayBoard(matrix,n,m);
  // movement(matrix,n,m);
  return 0;
}
