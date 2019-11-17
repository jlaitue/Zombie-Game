#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>
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

void createMatrix(int n, int m){
  // an array with 5 rows and 2 columns.
   int a[5][2] = { {0,0}, {1,2}, {2,4}, {3,6},{4,8}};

   // output each array element's value
   for ( int i = 0; i < 5; i++ )
      for ( int j = 0; j < 2; j++ ) {

         cout << "a[" << i << "][" << j << "]: ";
         cout << a[i][j]<< endl;
      }

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

    if (move == "x"){
      move = "STOP";
    }
  }
}

void fileReading(string matrix[][m]){
  string line;
  int rows=0,columns=0;

  fstream inFile;
  inFile.open("tableau.txt");

  if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
  }
  int xcount = 0, powcount=0, diamcount=0, monscount=0, whitecount=0;
  while (getline(inFile, line)) {
        cout<<"Analyzing row: "<<rows<<endl;
        // using printf() in all tests for consistency
        // cout<<line;
        // cout<<line.size();
        for(size_t i = 0; i < line.length(); i++)
        {
          // cout<<"Fila "<<i<<endl;
          if (line[i] == 'X'){
            cout<<"JODER UNA X ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "X";
            xcount ++;
          }
          else if (line[i] == '*'){
            cout<<"JODER UN POWERUP ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "*";
            powcount++;
          }
          else if (line[i] == '$'){
            cout<<"JODER UN DIAMANTE ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "$";
            diamcount++;

          }
          else if (line[i] == 'M'){
            cout<<"JODER UN MONSTRUO ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = "M";
            monscount++;
          }
          else if (line[i] == ' '){
            cout<<"JODER ESPACIO VACIO ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
            matrix[rows][i] = " ";
            whitecount++;
          }
          else if (line[i] == 'J'){
            cout<<"JODER JUGADOR ";
            cout<<"Coordenadas: "<<rows<<", "<<i<<"\n";
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
    system("pause");
    cout<<"\n\n";
}

int main() {
  string matrix[n][m];

  // for (size_t i = 0; i < n; i++) {
  //   for (size_t j = 0; j < m; j++) {
  //     matrix[i][j] = "X";
  //   }
  // }
  // movement(matrix,n,m);
  fileReading(matrix);
  printMatrix(matrix,n,m);

  return 0;
}
