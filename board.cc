#include <vector>
#include "board.h"
#include "cell.h"
#include "level.h"
using namespace std;


int minimumLevel = 0;
int maximumLevel = 4;

Board::Board( int r, int c, int sc, int hisc ): 
	row{r}, col{c}, score{sc}, hiScore{hisc} {
	for(int i=0; i < row; ++i) {
		vector<Cell> v;
		for(int j=0; j < col; ++j) {
			v.emplace_back(Cell{i,j});
		}
		theBoard.emplace_back(v);
	}
}

Board::~Board() { }

// private methods

void Board::drawCurrent( char type, shared_ptr<Block> b ) {
	if (type == 'I') setBlock(3,0,3,1,3,2,3,3,current);
	if (type == 'J') setBlock(2,0,3,0,3,1,3,2,current);
	if (type == 'L') setBlock(3,0,3,1,3,2,2,2,current);
	if (type == 'O') setBlock(2,0,2,1,3,0,3,1,current);
	if (type == 'Z') setBlock(2,0,2,1,3,1,3,2,current);
	if (type == 'S') setBlock(3,0,3,1,2,1,2,2,current);
	if (type == 'T') setBlock(2,0,2,1,2,2,3,1,current);
}

void Board::setLevel( int l ) {
	if (l == 0) level = make_shared<LevelZero>();
	if (l == 1) level = make_shared<LevelOne>();
	if (l == 2) level = make_shared<LevelTwo>();
	if (l == 3) level = make_shared<LevelThree>();
	if (l == 4) level = make_shared<LevelFour>();
	notifyViews();
}

void Board::popBlock() {
	int size = blocks.size();
	for(int i=0; i < size; ++i) {
		if (blocks[i].use_count() == 1) {
			addScore(blocks[i]->getScore());
			blocks.erase(blocks.begin() +i);
		}
	}
/*	
	for(auto b : blocks) {
		if (b.use_count() == 1) {
			addScore(b->getScore());
			blocks.erase(b);
		}
	}
*/}

void Board::deleteARow( int r ) {
	for(int i=0; i < col; ++i) setBlock(r,i, nullptr);
}



// OPERATIONS
void Board::createCurrent() {
	if (!theNext) current = level->createBlock(*this, level->getScore(), 0);
	else current = theNext;
	drawCurrent(current->getType(), current);
}

void Board::createNext() {
	theNext = level->createBlock(*this, level->getScore(), 0);
	notifyViews(*theNext);
}

void Board::createCurrent( char type ) {
	if (!theNext) current = level->createBlock(*this, level->getScore(), 0, type);
	else current = theNext;
	drawCurrent(current->getType(), current);
}

void Board::createNext( char type ) {
	theNext = level->createBlock(*this, level->getScore(), 0, type);
	notifyViews(*theNext);
}


void Board::replaceCurrent( char type ) {
	setBlock(2,0,2,1,2,2,2,3, nullptr);
	setBlock(3,0,3,1,3,2,3,3, nullptr);
	current = level->createBlock(*this, level->getScore(), 0, type);
	drawCurrent(current->getType(), current);
}

void Board::moveRight() { level->moveRight(*current); }

void Board::moveLeft() { level->moveLeft(*current); }

void Board::moveDown() { level->moveDown(*current); }

void Board::rotateCW() { level->rotateCW(*current); }

void Board::rotateCC() { level->rotateCC(*current); }

void Board::drop() { 
	level->drop(*current);
	blocks.emplace_back(current); 
}

void Board::dropBlocks( int r ) {
	for(int i=r-1; i >= 0; --i) {
		for(int j=0; j < col; ++j) {
			setBlock(i+1,j,theBoard[i][j].getBlock());
			setBlock(i,j,nullptr);
		}
	}
}

void Board::levelUp() {
	int nextLevel = level->getLevel() +1;
	if (nextLevel <= maximumLevel) setLevel(nextLevel);
}

void Board::levelDown() {
	int nextLevel = level->getLevel() -1;
	if (nextLevel >= minimumLevel) setLevel(nextLevel);
}

void Board::deleteRows( int r ) {
	int score = level->getScore();
	for(int i=r; i > r-4; --i) {
		if (isRowFilled(i)) {
			deleteARow(i);
			++score;
		}
	}
	addScore(score*score);
	popBlock();
}




// MUTATOR
void Board::attachView( const shared_ptr<View> v ) {
	views.emplace_back(v);
	for(auto &i : theBoard) {
		for(auto &j : i) j.attach(v);
	}
}

void Board::setBlock( int r, int c, const shared_ptr<Block> b ) {
	if (r == -1 && c == -1) return ;
	theBoard[r][c].setBlock(b);
}

void Board::setBlock( int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, const shared_ptr<Block> b ) {
	setBlock(r1,c1,b);
	setBlock(r2,c2,b);
	setBlock(r3,c3,b);
	setBlock(r4,c4,b);
}

void Board::addScore( int n ) { 
	score += n;
	if (score > hiScore) hiScore += n;
	notifyViews();
}

void Board::setScore( int n ) { 
	score = n; 
	notifyViews();
}

void Board::setHiScore( int n ) { 
	hiScore = n;
	notifyViews();
}





// ACCESSOR
int Board::getLevel() const { return level->getLevel(); }

int Board::getRow() const { return row; }

int Board::getCol() const { return col; }

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

shared_ptr<Block> Board::getCurrent() const { return current; }

bool Board::isEmpty( int r, int c ) const {
	if (r == -1 && c == -1) return true;
	else return theBoard[r][c].isEmpty();
}

bool Board::isEmpty( int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4 ) const {
	return isEmpty(r1,c1) && isEmpty(r2,c2) && isEmpty(r3,c3) && isEmpty(r4,c4);
}


bool Board::isRowFilled(int r) {
	for(int i=0; i<col; ++i){
		if(isEmpty(r,i)) return false;
	}
	return true;
}

bool Board::checkifLost() {
	for(auto c : theBoard[2]) {
		if (!c.isEmpty()) return false;
	}
	return true;
}

void Board::notifyViews() const { for(auto o : views) o->notify(*this); }

void Board::notifyViews( const Block &b ) const { for(auto o : views) o->notify(b); }



