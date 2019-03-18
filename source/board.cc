#include "board.h"
#include "cell.h"
#include "level.h"
#include <vector>
using namespace std;

#include <iostream>

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
	level = make_shared<LevelZero>();
}

Board::~Board() { }

// private methods

void Board::clearBoard() {
	for(auto v : theBoard) {
		for(auto c : v) c.setBlock(nullptr);
	}
}

void Board::drawCurrent(vector<int> info) {
	setBlock(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], current);
}

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
	for(int i=0; i < size;++i) {
		if ((i+1 == size && blocks[i].use_count() == 2) || blocks[i].use_count() <= 1) {
			addScore(blocks[i]->getScore());
			blocks.erase(blocks.begin() +i);
			--i;
			size = blocks.size();
		} 
	}
}

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
	vector<int> curInfo = current->getInfo(current->getForm());
	vector<int> newInfo = current->getInfo(type);
	int curSize = curInfo.size();
	int newSize = newInfo.size();
	for (int i = 0; i < curSize; i+=2){
		for (int j = 0; j < newSize; j+=2){
			if (curInfo[i] == newInfo[j] && curInfo[i+1] == newInfo[j+1]){
				newInfo[j] = -1;
				newInfo[j+1] = -1;
			}
		}
	}

	for (int k = 0; k < newSize; k+=2){
		if (!(isEmpty(newInfo[k], newInfo[k+1]))) {
			return;
		}
	}

	newInfo = current->getInfo(type);

	setBlock(curInfo[0],curInfo[1],curInfo[2],curInfo[3],curInfo[4],curInfo[5],curInfo[6],curInfo[7], nullptr);
	int row = current->getRow();
	int col = current->getCol();
	current = level->createBlock(*this, level->getScore(), 0, type);
	current->setCoord(row, col);
	drawCurrent(newInfo);	
}

void Board::moveRight() { level->moveRight(*current); }

void Board::moveLeft() { level->moveLeft(*current); }

void Board::moveDown() { level->moveDown(*current); }

void Board::rotateCW() { level->rotateCW(*current); }

void Board::rotateCC() { level->rotateCC(*current); }

void Board::drop() {
	blocks.emplace_back(current); 
	level->drop(*current);
}

void Board::dropBlocks( int r ) {
	for(int i=r-1; i >= 0; --i) {
		for(int j=0; j < col; ++j) {
			if (!theBoard[i][j].isEmpty()) {
				setBlock(i+1,j,theBoard[i][j].getBlock());
				setBlock(i,j,nullptr);
			}
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

int Board::deleteRows( int r ) {
	int deleteRows = 0;
	int score = level->getLevel();
	for(int i=r; i > r-4; --i) {
		if (isRowFilled(i)) {
			deleteARow(i);
			++score;
			++deleteRows;
			level->clear();
		}
	}
	addScore(score*score);
	popBlock();
	return deleteRows;
}

void Board::setSeed( int s ) { level->setSeed(s); }


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

void Board::restart() {
	current = nullptr;
	theNext = nullptr;
	blocks.clear();
	clearBoard();
	level = make_shared<LevelOne>();
	score = 0;
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



