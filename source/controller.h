
#ifndef _CONTROLLER_H_SSS
#define _CONTROLLER_H_

#include <string>
#include <fstream>
#include <map>
#include <memory>
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "window.h"

class Controller {

  public:
  // constructor of Controller
  Controller();

  // destructor of Controller
  ~Controller();

  // interpret the command line interface
  void cmdLine( int argc, char *argv[] );

  // starts the game
  void play( int argc, char *argv[] );
 
  // runs the game in text-only mode.
  void textMode();

  // sets the seed of random generator
  void setSeed(std::string);
 
  // uses 'file' instead of sequence.txt as a source of blocks for level 0.
  void scriptfile(std::string);

  // starts the game in level n.
  void startlevel(std::string);
 
  private:
  //---[member variables]---
  // board of the game
  std::shared_ptr<Board> board;
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<GraphicsDisplay> gd;
  std::shared_ptr<Xwindow> win;

  // stores the input.
  std::string input;

  // checks randomness;
  bool randomness;

  // textMode;
  bool textmode;

  // ifstream to read from file
  std::ifstream readfile;

  // typedef of SSSfunction pointers of class Controller.
  // - for readability, and easiness of use.
  typedef void (Controller::*command)();

  // stores command Name, and command Function* pair.
  std::map<std::string, command> cmdMap;
  
  //---[member functions]---
  // parses input and calls execute.
  // returns true Sif command is valid.
  // false otherwise. 
  void parseInput();

  /*void getInfo();*/

  // checks if command given by string is valid.
  // when complete, command is valid if stored in cmdMap.
  // when incomplete, command is valid if there is only
  // one corresponding command in cmdMap.
  bool checkCommand();
 
  // executes command given by string
  void execute();

  // creates a block
  void createBlock();

  //--command functions to be stored in cmdMap--
  // increments difficulty level by 1.
  void levelUp();
  
  // decrements difficulty level by 1.
  void levelDown();

  // moves the current block one cell to the left.
  void right();

  // moves the current block one cell to the right.
  void left();
  
  // moves the current block one cell down.
  void down();

  // drops the current block.
  void drop();

  // block functions used to replace current undropped block
  // with the stated block.
  void i();
  void j();
  void l();
  void o();
  void t();
  void s();
  void z();

  // rotates the block 90 degrees clockwise.
  void clockwise();
 
  // rotates the block 90 degress counterclockwise.
  void counterclockwise();
  
  // restores randomness during levels 3 and 4. 
  void rrandom();

  // removes randomness during levels 3 and 4.
  // instead takes sequence of blocks from file. 
  void noRandom();
  
  // executes the sequence of command from file.
  void sequence();

  // clears the board and starts a new game.
  void restart();

  // suggests a landing place for the current block.
  void hint();

  // renames an existing function
  void rename();
};

#endif
