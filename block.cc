#include <string>
#include "block.h"
#include "board.h"

using namespace std;


Block::Block( shared_ptr<Board> b, int s, int time ):
	board{b}, score{s}, timeStamp{time} { }

Block::~Block() { }


Block_I::Block_I( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_I::~Block_I() { }



char Block_I::getType() const { return 'I'; } 

string Block_I::drawBlock() const { return "IIII"; }





Block_J::Block_J( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_J::~Block_J() { }

char Block_J::getType() const { return 'J'; }

string Block_J::drawBlock() const { return "J\nJJJ"; }




Block_L::Block_L( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_L::~Block_L() { }

char Block_L::getType() const { return 'L'; }

string Block_L::drawBlock() const { return "  L\nLLL"; }




Block_O::Block_O( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_O::~Block_O() { }

char Block_O::getType() const { return 'O'; }

string Block_O::drawBlock() const { return "OO\nOO"; }




Block_S::Block_S( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_S::~Block_S() { }

char Block_S::getType() const { return 'S'; }

string Block_S::drawBlock() const { return " SS\nSS"; }




Block_Z::Block_Z( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_Z::~Block_Z() { }

char Block_Z::getType() const { return 'Z'; }

string Block_Z::drawBlock() const { return "ZZ\n ZZ"; }




Block_T::Block_T( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_T::~Block_T() { }

char Block_T::getType() const { return 'T'; }

string Block_T::drawBlock() const { return "TTT\n T"; }




Block_X::Block_X( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_X::~Block_X() { }

char Block_X::getType() const { return 'X'; }

string Block_X::drawBlock() const { return "X"; }
