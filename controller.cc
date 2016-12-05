#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>
#include "controller.h"
using namespace std;

//CONSTRUCTOR=====================================================================
Controller::Controller()
{
  randomness = true;
  textmode = false;

  board = make_shared<Board>();
  // define function pointers;
  command levelUp_ = &Controller::levelUp;
  command levelDown_ = &Controller::levelDown;
  command right_ = &Controller::right;
  command left_ = &Controller::left;
  command down_ = &Controller::down;
  command drop_ = &Controller::drop;
  command i_ = &Controller::i;
  command j_ = &Controller::j;
  command l_ = &Controller::l;
  command o_ = &Controller::o;
  command t_ = &Controller::t;
  command s_ = &Controller::s;
  command z_ = &Controller::z;
  command clockwise_ = &Controller::clockwise;
  command counterclockwise_ = &Controller::counterclockwise;
  command random_ = &Controller::rrandom;
  command noRandom_ = &Controller::noRandom;
  command sequence_ = &Controller::sequence;
  command restart_ = &Controller::restart;
  command hint_ = &Controller::hint;

  // insert to cmdMap;
  cmdMap["levelup"] = levelUp_;
  cmdMap["levelDown"] = levelDown_;
  cmdMap["right"] = right_;
  cmdMap["left"] = left_;
  cmdMap["down"] = down_;
  cmdMap["drop"] = drop_;
  cmdMap["I"] = i_;
  cmdMap["J"] = j_;
  cmdMap["L"] = l_;
  cmdMap["O"] = o_;
  cmdMap["T"] = t_;
  cmdMap["S"] = s_;
  cmdMap["Z"] = z_;
  cmdMap["clockwise"] = clockwise_;
  cmdMap["counterclockwise"] = counterclockwise_;
  cmdMap["random"] = random_;
  cmdMap["norandom"] = noRandom_;
  cmdMap["sequence"] = sequence_;
  cmdMap["restart"] = restart_;
  cmdMap["hint"] = hint_;
};
//===============================================================================


//DESTRUCTOR=====================================================================
Controller::~Controller(){
};
//===============================================================================

void Controller::cmdLine( int argc, char *argv[] ) {
  for (int i = 1; i < argc; i++){
    if (string(argv[i]) == "-text"){
      textMode();
    }
    else if (string(argv[i]) == "-seed"){
      if (i+1 >= argc) throw invalid_argument("seed number missing");
      setSeed(string(argv[++i]));
    }
    else if (string(argv[i]) == "-scriptfile"){
      if (i+1 >= argc) throw invalid_argument("scriptfile missing");
      scriptfile(string(argv[++i]));
    }
    else if (string(argv[i]) == "-startlevel"){
      if (i+i >= argc) throw invalid_argument("level missing");
      startlevel(string(argv[++i]));
    }
    else{
      cerr << "Invalid Command" << endl;
    }
  }
}

//PLAY===========================================================================
void Controller::play( int argc, char *argv[] ){
  try{ cmdLine(argc, argv); }
  catch(invalid_argument e) {
    cerr << e.what() << endl;
  }
  if (board->getLevel() == 0 && !(readfile.is_open())){
    cerr << "scriptfile not found" << endl;
    return ;
    //throw invalid_argument("Sequence file missing!");
  } 
  td = make_shared<TextDisplay>();
  board->attachView(td);

  if (textmode == false){
    win = make_shared<Xwindow>();
    gd = make_shared<GraphicsDisplay>(*win);
    board->attachView(gd);
  }

  board->setLevel(board->getLevel());
  createBlock();
  //getInfo();
  cout << *td;

  while (cin >> input){
    try {
      parseInput();
    } catch(out_of_range) {}
    cout << *td;
  }
  cout << "Game Over" << endl;
}
//===============================================================================

/*void Controller::getInfo(){
  vector<int> info = board->getInfo();
  vector<int>::iterator it;
  for (it = info.begin(); it != info.end(); it++){
    cout << *it << endl;
  }
}*/

//PARSEINPUT=====================================================================
void Controller::parseInput(){
  string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //find the first occurrence of alphabet;
  size_t pos = input.find_first_of(alphabet);
  int multiplierNum;
  string multiplier;

  //if there is a multiplier prefix:
  if (pos != 0){
    multiplier = input.substr(0, pos);
    input = input.substr(pos, input.length());
    cout << input << endl;
  } else { // else
    multiplier = "1";
  }

  //execute number of multiplier num times;
  multiplierNum = atoi(multiplier.c_str());
  for (int i = multiplierNum; i > 0; i--){
    execute();
  }
}
//===============================================================================


//CHECKCOMMAND===================================================================
bool Controller::checkCommand(){
  //string to store corresponding command;
  string cmd;
  int correspondence = 0;
  map<string, command>::iterator it;
  for (it = cmdMap.begin(); it != cmdMap.end(); it++){
    if (it->first.substr(0, input.length()) == input){
      correspondence++;
      // cmd = corresponding command;
      cmd = it->first;
    }
  }
  // check if cmd is a shortcut - if there is only 1 corresponding func;
  if (correspondence == 1){
    input = cmd;
    return true;
  }
  return false;
} 
//===============================================================================


//EXECUTE========================================================================
void Controller::execute(){
  map<string, command>::iterator it;
  //find input(command);
  it = cmdMap.find(input);
  //if not found;
  if (it == cmdMap.end()){
    //run checkCommand
    if (checkCommand()){
      //find input(command);
      it = cmdMap.find(input);
    }
  }
  //if input had been found;
  if (it != cmdMap.end())
  //run command;
  (this->*it->second)();
}
//===============================================================================


//CREATEBLOCK====================================================================
void Controller::createBlock(){
  if (randomness == false){
    char next;
    if (readfile >> next){
    board->createNext(next);
    board->createCurrent();
    } else {
      readfile.close();
      randomness = true;
    }
  }
  board->createCurrent();
  board->createNext();
}
//===============================================================================


//TEXTMODE=======================================================================
void Controller::textMode(){
  textmode = true;
}
//===============================================================================


//SETSEED========================================================================
void Controller::setSeed(string s){
  board->setSeed(atoi(s.c_str()));
}
//===============================================================================


//SCRIPTFILE=====================================================================
void Controller::scriptfile(string s){
  if (board->getLevel() == 0){
    readfile.open(s);
    randomness = false;
  }
}
//===============================================================================


//STARTLEVEL=====================================================================
void Controller::startlevel(string s){
  board->setLevel(atoi(s.c_str()));
}
//===============================================================================


//COMMANDS=======================================================================
void Controller::right(){
  board->moveRight();
}

void Controller::left(){
  board->moveLeft();
}

void Controller::down(){
  board->moveDown();
}

void Controller::drop(){
  board->drop();
  if (board->getCurrent()->isDropped()){
    createBlock();
  }
}

void Controller::clockwise(){
  board->rotateCW();
}

void Controller::counterclockwise(){
  board->rotateCC();
}

void Controller::levelUp(){
  board->levelUp();
}

void Controller::levelDown(){
  board->levelDown();
}

void Controller::i(){
  board->replaceCurrent('I');
}

void Controller::j(){
  board->replaceCurrent('J');
}

void Controller::l(){
  board->replaceCurrent('L');
}

void Controller::o(){
  board->replaceCurrent('O');
}

void Controller::t(){
  board->replaceCurrent('T');
}

void Controller::s(){
  board->replaceCurrent('S');
}

void Controller::z(){
  board->replaceCurrent('Z');
}

void Controller::rrandom(){}

void Controller::noRandom(){
  string file;
  cin >> file;
  readfile.open(file);
  randomness = false;
}

void Controller::sequence(){
  string file;
  if (cin >> file){
      ifstream sequence(file);
      while(!sequence.eof()){
        sequence >> input;
        try{parseInput();}
        catch(out_of_range){}
      }
  }
}

void Controller::restart(){
  board->restart();
}

void Controller::hint(){}
