#include <memory>
#include <cstdlib>
#include <string>
#include "level.h"
#include "block.h"
#include "block_i.h"
#include "block_j.h"
#include "block_l.h"
#include "block_o.h"
#include "block_s.h"
#include "block_z.h"
#include "block_t.h"
#include "block_x.h"
#include "board.h"
using namespace std;


Level::Level() { }

Level::~Level() { }

// non-random createBlock
shared_ptr<Block> Level::createBlock( Board &b, int s, int stamp, char t ) {
	if (t == 'I') return make_shared<Block_I>(b, s, stamp);
	if (t == 'J') return make_shared<Block_J>(b, s, stamp);
	if (t == 'S') return make_shared<Block_S>(b, s, stamp);
	if (t == 'Z') return make_shared<Block_Z>(b, s, stamp);
	if (t == 'O') return make_shared<Block_O>(b, s, stamp);
	if (t == 'L') return make_shared<Block_L>(b, s, stamp);
	if (t == 'T') return make_shared<Block_T>(b, s, stamp);
	if (t == 'X') return make_shared<Block_X>(b, s, stamp);
	else throw invalid_argument{string{t}};
}

void Level::rotateCW( Block &b ) const { b.rotateCW(); }

void Level::rotateCC( Block &b ) const { b.rotateCC(); }

void Level::moveRight( Block &b ) const { b.moveRight(); }

void Level::moveLeft( Block &b ) const { b.moveLeft(); }

void Level::moveDown( Block &b ) const { b.moveDown(); }

void Level::drop( Block &b ) { 
	b.drop(); }

void Level::setSeed( int s ) { 
	seed = s;
	srand(seed);
}

void Level::clear() { fallen = 0; }

int Level::getFallen() const { return fallen; }

LevelZero::LevelZero(): Level() { }

LevelZero::~LevelZero() { }

shared_ptr<Block> LevelZero::createBlock( Board &b, int s, int stamp ) { 
	return nullptr;
}


int LevelZero::getScore() const { return 1; }

int LevelZero::getLevel() const { return 0; }







LevelOne::LevelOne(): Level() { }

LevelOne::~LevelOne() { }


// random createBlock
shared_ptr<Block> LevelOne::createBlock( Board &b, int s, int stamp ) {
//	srand(seed);
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


shared_ptr<Block> LevelTwo::createBlock( Board &b, int s, int stamp ) {
//	srand(seed);
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

shared_ptr<Block> LevelThree::createBlock( Board &b, int s, int stamp ) {
//	srand(seed);
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

void LevelThree::rotateCW( Block &b ) const {
	b.rotateCW();
	b.moveDown();
}

void LevelThree::rotateCC( Block &b ) const {
	b.rotateCC();
	b.moveDown();	
}

void LevelThree::moveRight( Block &b ) const {
	b.moveRight();
	b.moveDown();
}

void LevelThree::moveLeft( Block &b ) const {
	b.moveLeft();
	b.moveDown();
}

void LevelThree::moveDown( Block &b ) const {
	b.moveDown();
	b.moveDown();
}

int LevelThree::getScore() const { return 16; }

int LevelThree::getLevel() const { return 3; }








LevelFour::LevelFour(): Level() { }

LevelFour::~LevelFour() { }

shared_ptr<Block> LevelFour::createBlock( Board &b, int s, int stamp ) {
	// dropping 1x1 block
	if (fallen == 5) {
		auto x = make_shared<Block_X>(b, s, stamp);
		x->drop();
		clear();
	}

//	srand(seed);
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

void LevelFour::rotateCW( Block &b ) const {
	b.rotateCW();
	b.moveDown();
}

void LevelFour::rotateCC( Block &b ) const {
	b.rotateCC();
	b.moveDown();	
}

void LevelFour::moveRight( Block &b ) const {
	b.moveRight();
	b.moveDown();
}

void LevelFour::moveLeft( Block &b ) const {
	b.moveLeft();
	b.moveDown();
}

void LevelFour::moveDown( Block &b ) const {
	b.moveDown();
	b.moveDown();
}

void LevelFour::drop( Block &b ) {
	++fallen;
	b.drop();
}

int LevelFour::getScore() const { return 25; }

int LevelFour::getLevel() const { return 4; }



