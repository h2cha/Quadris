#include <iostream>
#include <stdlib.h>
#include "controller.h"
using namespace std;

Controller::Controller()
{
  randomness = true;
  board = make_shared<Board>();
  td = make_shared<TextDisplay>();
  board->attachView(td);
  board->setLevel(2);
  board->createBlock();
  cout << *td;
  // define function pointers
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
  
  // insert to cmdMap
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

Controller::~Controller(){
//  map<string, command>::iterator it;
//  for (it = cmdMap.begin(); it != cmdMap.end(); it++){
//    delete it->second;
//  }
};

void Controller::play(){
  while (cin >> input){
    parseInput();
    cout << *td;
  }
  cout << "Game Over" << endl;
}

void Controller::parseInput(){
  string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  size_t pos = input.find_first_of(alphabet);
  int multiplierNum;
  string multiplier;

  if (pos != 0){
    multiplier = input.substr(0, pos);
    input = input.substr(pos, input.length());
    cout << input << endl;
  } else {
    multiplier = "1";
  }

  multiplierNum = atoi(multiplier.c_str());
  for (int i = multiplierNum; i > 0; i--){
    execute();
  }
}

bool Controller::checkCommand(){
  string cmd;
  int correspondence = 0;
  map<string, command>::iterator it;
  for (it = cmdMap.begin(); it != cmdMap.end(); it++){
    if (it->first.substr(0, input.length()) == input){
      correspondence++;
      cmd = it->first;
      cout << it->first << endl;
    }
  }
  if (correspondence == 1){
    cout << correspondence << endl;
    input = cmd;
    return true;
  }
  return false;
} 

void Controller::execute(){
  map<string, command>::iterator it;
  it = cmdMap.find(input);
  cout << "0" << endl;
  if (it == cmdMap.end()){
    if (checkCommand()){
      cout << "1" << endl;
      it = cmdMap.find(input);
    }
  }
  if (it != cmdMap.end())
  (this->*it->second)();
}

void Controller::textMode(){}

  // sets the seed of random generator
void Controller::setSeed(int i){}
 
  // uses 'file' instead of sequence.txt as a source of blocks for level 0.
void Controller::scriptfile(string s){}

  // starts the game in level n.
void Controller::startlevel(int i){}

void Controller::createBlock(){
  if (randomness == false){
    char current;
    char next;
    (readfile >> current);
    if (readfile >> next){
    board->createBlock(current, next);
    } else {
      readfile.close();
    }
  }
  board->createBlock();
}

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
  char cur;
  readfile.open(file);
  readfile >> cur;
  board->replaceCurrent(cur);
  randomness = false;
}

void Controller::sequence(){
  string file;
  if (cin >> file){
      ifstream sequence(file);
      while(!sequence.eof()){
        sequence >> input;
        parseInput();
      }
  }
}

void Controller::restart(){}

void Controller::hint(){}
