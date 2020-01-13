#include "../inc/Game.hpp"
#include "../inc/Board.hpp"
#include "../inc/Player.hpp"
#include "../inc/Helper.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <ncurses.h>

using namespace std;

int Game::gameCount = 0;

Game::Game(){
  gameCount++;
  identifier = gameCount;
  gameBlock = 0;
  gameType = 1;
  totalDiamonds = 0;
  virusMode = 0;
  // cout<<"Game created"<<"\n";
  // cout<<"Game id: "<<identifier<<"\n";
}

void Game::addBoard(int level, string filename){
  Board board;

  if (gameType == 1) {
    board.createTheMatrix(level, filename);
  }
  else{
    board.readBoard(level, filename);
  }
  if (virusMode or level == 6) {
    board.switchVirusMode();
  }
  boards.push_back(board);
  totalDiamonds += board.getNumberDiamonds();
}

void Game::getPlayerInfo(){
  char inputName[100];
  char inputLevel[100];
  char inputGameChoice[100];
  char inputDesiredBoards[100];
  char inputVirusMode[100];
  const char *cstr;

  string newName;

  mvaddstr(4, 0, "This is Ultron's board game for saving the planet!");
  mvaddstr(5, 0, "You should avoid getting eaten by monsters and finish all levels!");
  mvaddstr(6, 0, "Before we begin we need some information to create a game suited to your liking");
  mvaddstr(8, 0, "PRESS ANY KEY TO CONTINUE...");
  refresh();
  getch();
  mvaddstr(2,0,"");
  clrtobot();

  mvaddstr(4, 0, "Enter your name: ");
  refresh();
  getstr(inputName);
  newName = inputName;
  cstr = player.updateName(newName).c_str();

  mvprintw(4, 0, "WELCOME TO THE AVENGERS TOWER | %s | ", cstr);

  // We ask for the type of game the user wants
  mvaddstr(6, 0, "Please choose the type of game you want Random = (1) ||  User Boards = (2): ");
  refresh();
  getstr(inputGameChoice);
  gameType = validateInputValue(6, inputGameChoice, 1, 2);
  mvaddstr(6,0,"");
  clrtoeol();
  if (gameType == 1) {
    int maxcols = COLS-1;
    mvprintw(6, 0, "GAME TYPE SELECTED: RANDOM");
    mvaddstr(10, maxcols/2-15, "BLOCK 1 -> 1 Stage  of difficulty 1");
    mvaddstr(11, maxcols/2-15, "BLOCK 2 -> 2 Stages of difficulty 2");
    mvaddstr(12, maxcols/2-15, "BLOCK 3 -> 3 Stages of difficulty 3");
    mvaddstr(13, maxcols/2-15, "BLOCK 4 -> 4 Stages of random difficulty 3-5");
    mvaddstr(14, maxcols/2-15, "BLOCK 5 -> 5 Stages of random difficulty 3-5");
    mvaddstr(15, maxcols/2-15, "BLOCK 6 -> 6 Stages of random difficulty 3-5");
    mvaddstr(16, maxcols/2-15, "BLOCK 7 -> 7 Stages of difficulty 6");
    mvaddstr(17, maxcols/2-15, "BLOCK 8 -> 8 Stages of difficulty 6");
    mvaddstr(18, maxcols/2-15, "BLOCK 9 -> 9 Stages of difficulty 6");
    mvaddstr(20, maxcols/2-15, "Virus mode is ENABLED in difficulty level 6");
    mvaddstr(8, 0, "Please enter the game BLOCK you want to play from 1 to 9: ");
    refresh();
    getstr(inputLevel);
    gameBlock = validateInputValue(8, inputLevel, 1, 9);
    mvaddstr(8,0,"");
    clrtoeol();
    mvprintw(8, 0, "GAME BLOCK SELECTED: %d", gameBlock);
  }
  else {
    mvprintw(6, 0, "GAME TYPE SELECTED: USER BOARDS", gameType);

    mvaddstr(8, 0, "Please enter the number of boards you would like to play: ");
    refresh();
    getstr(inputDesiredBoards);
    gameStages = validateInputValue(8, inputDesiredBoards, 1, 5);
    mvaddstr(8,0,"");
    clrtoeol();
    mvprintw(8, 0, "NUMBER OF STAGES IN GAME: %d", gameStages);
    refresh();
    for (int i = 0; i < gameStages; i++) {
      char inputFileName[100];
      string boardFileName;
      fstream file;

      mvaddstr(10,0,"");
      clrtobot();
      mvprintw(10, 0, "Enter the file name you would like to test for stage %d/%d: boards/",i+1, gameStages);
      refresh();
      getstr(inputFileName);
      boardFileName = inputFileName;

      file.open("../boards/"+boardFileName);

      while (!file) {
        mvaddstr(10,0,"");
        clrtobot();
        mvprintw(10, 0, "The filename you entered does not exist, try again: boards/");
        refresh();
        getstr(inputFileName);
        boardFileName = inputFileName;
        file.open("../boards/"+boardFileName);
      }
      userFileNames.push_back(boardFileName);
    }
  }

  if (gameBlock < 7) {
    mvaddstr(22, 0, "Do you want to activate Virus Mode? Yes = (1) No = (0): ");
    refresh();
    getstr(inputVirusMode);
    virusMode = validateInputValue(22, inputVirusMode, 0, 1);
    mvaddstr(22,0,"");
    clrtoeol();
    if (virusMode) {
      mvprintw(22, 0, "VIRUS MODE ACTIVATED");
    }
    else {
      mvprintw(22, 0, "VIRUS MODE DISABLED");
    }
  }

  mvaddstr(LINES-1, 0, "PRESS ANY KEY TO BEGIN THE GAME...");
  refresh();
  getch();

}

void Game::run(){
  size_t stage = 0;
  bool playing = true;
  string userStage = "";
  int maxlines, maxcols;

  initscr();
  raw();
  clear();
  start_color();

  init_pair(1,COLOR_GREEN, COLOR_BLACK);
  init_pair(2,COLOR_RED, COLOR_BLACK);
  init_pair(3,COLOR_YELLOW, COLOR_BLACK);
  init_pair(4,COLOR_BLUE, COLOR_BLACK);
  init_pair(5,COLOR_CYAN, COLOR_BLACK);
  init_pair(6,COLOR_WHITE, COLOR_BLACK);

  maxlines = LINES-1;
  maxcols = COLS-1;

  mvaddstr(0, maxcols/2-15, "<| ULTRON'S BOARD GAME v1.0 |>");
  mvaddstr(1, maxcols/2-19, "ALEXANDER MORAKHOVSKI | JULIAN LECHUGA");

  getPlayerInfo();

  if (gameType == 1) {
    loadRandomBoards();
  }
  else {
    loadUserBoards();
  }

  mvaddstr(LINES-2, 0, "Terminar de enlistar...");
  refresh();
  getch();

  noecho();
  while (playing == true) {
    if (stage <= (boards.size()-1)) {
      mvprintw(3, 12, "Game stage %d/%d", stage+1, boards.size());
      mvprintw(3, maxcols/2-20, "Stage difficulty %d", boards[stage].getBoardLevel());
      userStage = boards[stage].play(player);

      if (userStage == "KILL") {
        playing = false;
        mvprintw(27, 0,"");
        clrtoeol();
        mvaddstr(27, maxcols/2-25, "GAME TERMINATED BY PLAYER");
      }
      else if (userStage == "NEXT") {
        stage++;
        mvprintw(7, maxcols/2+10, "REACHED NEW LEVEL!");
        refresh();
      }
    }
    else {
      playing = false;
      mvprintw(27, 0,"");
      clrtoeol();
      mvaddstr(27, maxcols/2-25, "CONGRATULATIONS! YOU COMPLETED ALL LEVELS!");
    }
  }

  // Each live is worth 3 diamonds, so we increment the respective amount
  for (int i = 0; i < 3*(player.Lives()-3); i++) {
    player.incrementDiamonds();
  }
  mvprintw(28, maxcols/2-25, "FINAL SCORE: %d DIAMONDS COLLECTED OUT OF %d", player.Diamonds(), totalDiamonds);
  // We add the total number of lives left to the total diamonds collected
  if (player.Diamonds() == totalDiamonds) {
    mvprintw(29, maxcols/2-25, "YOU REACHED THE HIGHEST SCORE, CONGRATS MATE!", player.Diamonds(), totalDiamonds);
  }
  mvaddstr(maxlines, 0, "PRESS ANY KEY TO EXIT... ");
  refresh();
  getch();
  endwin();
  exit(0);
}

void Game::loadRandomBoards(){
  srand (time(NULL));
  // List of cool names for boards jiji :D
  string boardNames[] = { "akiva", "alderaan", "behpour","bogano",
    "chandrila", "corellia", "tatooine","dantooine","lothal", "geonosis",
    "kuat","iego","coruscant", "kessel", "kamino","hoth", "jedha", "exegol",
    "devaron"};
  // The block selected defines the number of stages to play in the game for the
  // RANDOM type game
  gameStages = gameBlock;
  // The game level selected also defines the difficulty for each board in
  // difficulty levels 1 to 6
  int boardLevel = gameBlock;
  string name, path, filename, ext = ".board";
  for (int i = 0; i < gameStages; i++) {
    name = boardNames[rand() % 17];
    filename = "/"+to_string(i)+name+ext;
    // If game block 7, 8, 9 is selected then a board of level 6 is created
    if (gameBlock >= 7) {
      boardLevel = 6;
    }
    path = "../boards/level_"+to_string(boardLevel);

    addBoard(boardLevel, path+filename);
  }
}

void Game::loadUserBoards(){
  srand (time(NULL));
  string path = "../boards/";
  for (int i = 0; i <  gameStages; i++) {
    addBoard(gameBlock, path+userFileNames[i]);
  }
}

Game::~Game(){
  // cout<<"Game "<<identifier<<" destroyed."<<"\n";
}
