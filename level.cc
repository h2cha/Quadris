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

void Level::rotateCW() { b.rotateCW(); }

void Level::rotateCC() { b.rotateCC(); }

void Level::moveRight() { b.moveRight(); }

void Level::moveLeft() { b.moveLeft(); }

void Level::moveDown() { b.moveDwon(); }

void Level::drop() { b.drop(); }

void Level::clear() { fallen = 0; }



LevelZero::LevelZero(): Level() { }

LevelZero::~LevelZero() { }

shared_ptr<Block> LevelZero::createBlock( shared_ptr<Board> b, int s, int stamp ) const { 
	return nullptr;
}


int LevelZero::getScore() const { return 1; }

int LevelZero::getLevel() const { return 0; }







LevelOne::LevelOne(): Level() { }

LevelOne::~LevelOne() { }


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


int LevelOne::getScore() const { return 4; }

int LevelOne::getLevel() const { return 1; }




LevelTwo::LevelTwo(): Level() { }

LevelTwo::~LevelTwo() { }


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

int LevelTwo::getScore() const { return 9; }

int LevelTwo::getLevel() const { return 2; }





LevelThree::LevelThree(): Level() { }

LevelThree::~LevelThree() { }

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

void LevelThree::rotateCW() const {
	b.rotateCW();
	b.moveDown();
}

void LevelThree::rotateCC() const {
	b.rotateCC();
	b.moveDown();	
}

void LevelThree::moveRight() const {
	b.moveRight();
	b.moveDown();
}

void LevelThree::moveLeft() const {
	b.moveLeft();
	b.moveDown();
}

void LevelThree::moveDown() const {
	b.moveDown();
	b.moveDown();
}

int LevelThree::getScore() const { return 16; }

int LevelThree::getLevel() const { return 3; }








LevelFour::LevelFour(): Level() { }

LevelFour::~LevelFour() { }

shared_ptr<Block> LevelFour::createBlock( shared_ptr<Board> b, int s, int stamp ) const {
	// dropping 1x1 block
	if (fallen == 5) {
		auto x = make_share<Block_X>(b, s, stamp);
		x.drop();
		clear();
	}

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

void LevelFour::rotateCW() const {
	b.rotateCW();
	b.moveDown();
}

void LevelFour::rotateCC() const {
	b.rotateCC();
	b.moveDown();	
}

void LevelFour::moveRight() const {
	b.moveRight();
	b.moveDown();
}

void LevelFour::moveLeft() const {
	b.moveLeft();
	b.moveDown();
}

void LevelFour::moveDown() const {
	b.moveDown();
	b.moveDown();
}

void LevelFour::drop() const {
	b.drop();
	++fallen;
}

int LevelFour::getScore() const { return 25; }

int LevelFour::getLevel() const { return 4; }

