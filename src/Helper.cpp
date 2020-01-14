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

void help(int helpRow0){
  mvaddstr(helpRow0+1, 5, "- Player (O) you need to collect as many Diamonds ($) as you can throughout the game");
  mvaddstr(helpRow0+2, 5, "- Diamonds ($) open the Doors (#)->(+) through which you can access new stages");
  mvaddstr(helpRow0+3, 5, "- 3 Diamonds ($) allow you to buy 1 live point");
  mvaddstr(helpRow0+4, 5, "- Powerups (*) can teleport you to a random position in the board");
  mvaddstr(helpRow0+5, 5, "- 5 Powerups (*) allow you to automatically change to the next stage, after opening a door!");
  mvaddstr(helpRow0+6, 5, "- Avoid crashing with Monsters (M) as they eat your life points!");
  mvaddstr(helpRow0+7, 5, "- Monsters (M) move randomly across the board. Be careful!");
  mvaddstr(helpRow0+8, 5, "- Virus mode makes the Monsters reproduce and attack you fiercely");
  mvaddstr(helpRow0+9, 5, "- Virus mode can be turned on/off Virus Mode in levels 1 to 5");
  mvaddstr(helpRow0+10, 5, "- Virus mode is PERMANENT in level 6");
  mvaddstr(helpRow0+11, 5, "- Remaining lives are accounted as diamonds collected");
  mvaddstr(helpRow0+12, 5, "- There two types of game modes RANDOM and USER BASED");
  mvaddstr(helpRow0+13, 5, "- RANDOM mode generates random boards for you to play along different stages");
  mvaddstr(helpRow0+14, 5, "- USER BASED allows you to select which boards you want to try");
  mvaddstr(helpRow0+15, 5, "- USER BASED allows you to select which boards you want to try");
  refresh();
}

void helpCreator(int helpRow0){
  mvaddstr(helpRow0, 5, "- In this v1.0 the size of the board is fixed to 20x40 elements");
  mvaddstr(helpRow0+1, 5, "- You can create boards with different types of elements");
  mvaddstr(helpRow0+2, 5, "- The elements are Monsters (M), Diamonds ($), Doors (#), Powerups (*) and Walls (X)");
  mvaddstr(helpRow0+3, 5, "- In order to create a good playing experience you can add up to 30 elements of each type");
  mvaddstr(helpRow0+4, 5, "- You can create up to 10 boards each time");
  mvaddstr(helpRow0+5, 5, "- Each board file created is stored in boards/user");
  mvaddstr(helpRow0+7, 5, "  Let's begin creating!");
  refresh();
}
