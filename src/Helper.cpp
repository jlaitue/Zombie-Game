#include "../inc/Helper.h"
#include <string>
#include <ncurses.h>
#include <sstream>

using namespace std;
//
int validateInputValue(int windowLine, char *inputAttribute, int rangeInit, int rangeEnd){
  string inputStr;
  int value;
  inputStr = inputAttribute;
  bool validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);
  bool acceptedInput = false;
  bool rangeInvalid = false;

  while(!acceptedInput){
    while (!validNumber) {
      mvaddstr(windowLine,0,"");
      clrtoeol();
      if(rangeInvalid){
        mvprintw(windowLine, 0, "The value entered must be in range [%d,%d], please try again:  ", rangeInit, rangeEnd);
        rangeInvalid = false;
      }
      else {
        mvprintw(windowLine, 0, "The value you entered is not a number, please try again: ");
      }
      refresh();
      getstr(inputAttribute);
      inputStr = inputAttribute;
      validNumber = (inputStr.find_first_not_of( "0123456789" ) == string::npos);
    }
    istringstream(inputStr) >> value;

    if (value >= rangeInit and value <= rangeEnd) {
      acceptedInput = true;
    }
    else {
      validNumber = false;
      rangeInvalid = true;
    }
  }
  return value;
}

void colorCoding(char element, int &colorCode){
  if (element == 'O') {
    colorCode = 1;
  }
  else if (element == 'M') {
    colorCode = 2;
  }
  else if (element == '*') {
    colorCode = 3;
  }
  else if (element == '$') {
    colorCode = 4;
  }
  else if (element == '.') {
    colorCode = 5;
  }
  else if (element == '#') {
    colorCode = 2;
  }
  else if (element == '+') {
    colorCode = 5;
  }
  else{
    colorCode = 6;
  }
}

std::string columnOrientation(){
    if (rand() % 2 == 0)
        return "horizontal";
    else return "vertical";
}
