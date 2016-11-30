#include <memory>
#include <cstdlib>
#include <time.h>
#include "level.h"
#include "block.h"
#include "board.h"
using namespace std;


Level::Level() { }

Level::~Level() { }

// non-random createBlock
shared_ptr<Block> Level::createBlock( shared_ptr<Board> b, int s, int stamp, char t ) const {
	if (t == 'I') return make_shared<Block_I>(b, s, stamp);
	if (t == 'J') return make_shared<Block_J>(b, s, stamp);
	if (t == 'S') return make_shared<Block_S>(b, s, stamp);
	if (t == 'Z') return make_shared<Block_Z>(b, s, stamp);
	if (t == 'O') return make_shared<Block_O>(b, s, stamp);
	if (t == 'L') return make_shared<Block_L>(b, s, stamp);
	if (t == 'T') return make_shared<Block_T>(b, s, stamp);
	if (t == 'X') return make_shared<Block_X>(b, s, stamp);
	else return nullptr;
}


LevelZero::LevelZero(): Level() { }

LevelZero::~LevelZero() { }

shared_ptr<Block> LevelZero::createBlock( shared_ptr<Board> b, int s, int stamp ) const { 
	return nullptr;
}


int LevelZero::getScore() const { return 1; }



LevelOne::LevelOne(): Level() { }

LevelOne::~LevelOne() { }

int LevelOne::getScore() const { return 4; }

// random createBlock
shared_ptr<Block> LevelOne::createBlock( shared_ptr<Board> b, int s, int stamp ) const {
	srand(time(nullptr));
	int num = rand() % 12;
	if (num == 0) return make_shared<Block_S>(b, s, stamp);
	if (num == 1) return make_shared<Block_Z>(b, s, stamp);
	if (num == 2 || num == 3) return make_shared<Block_I>(b, s, stamp);
	if (num == 4 || num == 5) return make_shared<Block_J>(b, s, stamp);
	if (num == 6 || num == 7) return make_shared<Block_O>(b, s, stamp);
	if (num == 8 || num == 9) return make_shared<Block_L>(b, s, stamp);
	if (num == 10 || num == 11) return make_shared<Block_T>(b, s, stamp);
	else return nullptr;
}



LevelTwo::LevelTwo(): Level() { }

LevelTwo::~LevelTwo() { }

int LevelTwo::getScore() const { return 9; }


shared_ptr<Block> LevelTwo::createBlock( shared_ptr<Board> b, int s, int stamp ) const {
	srand(time(nullptr));
	int num = rand() % 7;
	if (num == 0) return make_shared<Block_S>(b, s, stamp);
	if (num == 1) return make_shared<Block_Z>(b, s, stamp);
	if (num == 2) return make_shared<Block_I>(b, s, stamp);
	if (num == 3) return make_shared<Block_J>(b, s, stamp);
	if (num == 4) return make_shared<Block_O>(b, s, stamp);
	if (num == 5) return make_shared<Block_L>(b, s, stamp);
	if (num == 6) return make_shared<Block_T>(b, s, stamp);
	else return nullptr;
}


LevelThree::LevelThree(): Level() { }

LevelThree::~LevelThree() { }

int LevelThree::getScore() const { return 16; }


shared_ptr<Block> LevelThree::createBlock( shared_ptr<Board> b, int s, int stamp ) const {
	srand(time(nullptr));
	int num = rand() % 9;
	if (num == 0 || num == 1) return make_shared<Block_S>(b, s, stamp);
	if (num == 2 || num == 3) return make_shared<Block_Z>(b, s, stamp);
	if (num == 4) return make_shared<Block_I>(b, s, stamp);
	if (num == 5) return make_shared<Block_J>(b, s, stamp);
	if (num == 6) return make_shared<Block_O>(b, s, stamp);
	if (num == 7) return make_shared<Block_L>(b, s, stamp);
	if (num == 8) return make_shared<Block_T>(b, s, stamp);
	else return nullptr;
}


LevelFour::LevelFour(): Level() { }

LevelFour::~LevelFour() { }

int LevelFour::getScore() const { return 25; }


shared_ptr<Block> LevelFour::createBlock( shared_ptr<Board> b, int s, int stamp ) const {
	srand(time(nullptr));
	int num = rand() % 9;
	if (num == 0 || num == 1) return make_shared<Block_S>(b, s, stamp);
	if (num == 2 || num == 3) return make_shared<Block_Z>(b, s, stamp);
	if (num == 4) return make_shared<Block_I>(b, s, stamp);
	if (num == 5) return make_shared<Block_J>(b, s, stamp);
	if (num == 6) return make_shared<Block_O>(b, s, stamp);
	if (num == 7) return make_shared<Block_L>(b, s, stamp);
	if (num == 8) return make_shared<Block_T>(b, s, stamp);
	else return nullptr;
}

