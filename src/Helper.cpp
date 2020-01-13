#include "../inc/Helper.h"
#include "../inc/Element.hpp"
#include "../inc/Player.hpp"
#include <string>
#include <ncurses.h>
#include <sstream>

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
