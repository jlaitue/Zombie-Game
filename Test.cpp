#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>
using namespace std;

const size_t n = 5;
const size_t m = 10;
// void createGrid(int n, int m){
//   int i, j;
//   string arr1[n][m];
//
//   //This will allow you to input the numbers individually to fill the array.
//   for (i = 0; i <= 7; i++)
//        for (j = 0; j <= 7; j++)
//              arr1[i][j] = " X ";
//
//   //This will output the array.
//   for (i = 0; i <= 7; i++)
//        {
//        for (j = 0; j <= 7; j++)
//              cout << arr1[i][j];
//        cout << endl;
//        }
// }
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
  matrix[rowPosition][colPosition] = "J";
  cout<<"Intial position (x,y) =  "<<rowPosition<<", "<<colPosition<<endl;
  cout<<"Initialized matrix: \n\n";
  printMatrix(matrix,n,m);
  while (move != "STOP") {
    cout<<"\nEnter move: ";
    cin>>move;
    if (move == "w"){
      matrix[rowPosition][colPosition]="X";
      rowPosition --;
      matrix[rowPosition][colPosition]="J";
      cout<<"Moving UP"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }
    if (move == "s"){
      matrix[rowPosition][colPosition]="X";
      rowPosition ++;
      matrix[rowPosition][colPosition]="J";
      cout<<"Moving DOWN"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }
    if (move == "d"){
      matrix[rowPosition][colPosition]="X";
      colPosition++;
      matrix[rowPosition][colPosition]="J";
      cout<<"Moving RIGHT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }
    if (move == "a"){
      matrix[rowPosition][colPosition]="X";
      colPosition--;
      matrix[rowPosition][colPosition]="J";
      cout<<"Moving LEFT"<<endl;
      cout<<"(x,y) = ("<<rowPosition<<", "<<colPosition<<")"<<endl;
      printMatrix(matrix,n,m);
    }
    if (move == "x"){
      move = "STOP";
    }
  }
}

void fileReading(){
  // string line;
  // int rows=0,columns=0;
  //
  // fstream inFile;
  // inFile.open("tableau.txt");
  //
  // if (!inFile) {
  //   cerr << "Unable to open file datafile.txt";
  //   exit(1);   // call system to stop
  // }
  // while (getline(inFile, line)) {
  //   int xcont = 0, astcont=0, diamcount=0;
  //       // using printf() in all tests for consistency
  //       // cout<<line;
  //       // cout<<line.size();
  //       for(unsigned int i = 0; i < line.length(); i++)
  //       {
  //         // cout<<"Fila "<<i<<endl;
  //         if (line[i] == 'X'){
  //           // cout<<"JODER UNA X ";
  //           xcont ++;
  //         }
  //         else if (line[i] == '*'){
  //           // cout<<"JODER UN POWERUP ";
  //           astcont++;
  //         }
  //         else if (line[i] == '$'){
  //           diamcount++;
  //
  //         }
  //       }
  //
  //
  //       // printf(line);
  //       printf("\n");
  //       // printf(line.length())s;
  //       rows ++;
  //       cout<<"Row: "<<rows<<endl;
  //       cout<<"Amount X "<<xcont<<endl;
  //       cout<<"Amount * "<<astcont<<endl;
  //       cout<<"Amount $ "<<diamcount<<endl;
  //   }
  //   columns = line.size();
  //   cout<<"Rows: "<<rows<<endl;
  //   cout<<"Columns: "<<columns;
  // createGrid(8,8);
  // system("pause");
}

int main() {


  string matrix[n][m];

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      matrix[i][j]="X";
    }
  }
  movement(matrix,n,m);

  return 0;
}
