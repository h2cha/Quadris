#include <vector>
#include "board.h"
#include "cell.h"
#include "level.h"
using namespace std;


Board::Board( int l, int r, int c, int sc, int hisc ): 
	row{r}, col{c}, score{sc}, hiScore{hisc} {
	if (l == 0) level = make_shared<LevelZero>();
	if (l == 1) level = make_shared<LevelOne>();
	if (l == 2) level = make_shared<LevelTwo>();
	if (l == 3) level = make_shared<LevelThree>();
	if (l == 4) level = make_shared<LevelFour>();
	for(int i=0; i < row; ++i) {
		vector<Cell> v;
		for(int j=0; j < col; ++j) {
			v.emplace_back(Cell{i,j});
		}
		theBoard.emplace_back(v);
	}
}

Board::~Board() { }





// OPERATOR
void Board::rotateCW() { level->rotateCW(*current); }

void Board::rotateCC() { level->rotateCC(*current); }

void Board::moveRight() { level->moveRight(*current); }

void Board::moveLeft() { level->moveLeft(*current); }

void Board::moveDown() { level->moveDown(*current); }

//void Board::drop() { 
//	level->drop(*current);
//	blocks.emplace_back(current); 
//}





// MUTATOR
void Board::attachView( const shared_ptr<View> v ) {
	for(auto &i : theBoard) {
		for(auto &j : i) j.attach(v);
	}
}

void Board::setBlock( int r, int c, const std::shared_ptr<Block> b ) {
	theBoard[r][c].setBlock(b);
}

void Board::addScore( int n ) { 
	score += n;
	if (score > hiScore) hiScore += n;
}

void Board::setScore( int n ) { score = n; }

void Board::setHiScore( int n ) { hiScore = n; }





// ACCESSOR
int Board::getRow() const { return row; }

int Board::getCol() const { return col; }

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

shared_ptr<Block> Board::getCurrent() const { return current; }

bool Board::isEmpty( int x, int y ) const {
	return theBoard[x][y].isEmpty();
}

bool Board::isEmpty( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 ) const {
	return isEmpty(x1,y1) && isEmpty(x2,y2) && isEmpty(x3,y3) && isEmpty(x4,y4);
}


bool Board::isRowClear(int r) {
	bool clear=true;
	for(int i=0; i<col; ++i){
		if(!isEmpty(r,i)){
			clear = false;
			break;
		}
	}
	return clear;
}
bool Board::isAllClear() {
	bool clear=true;
	for(int i=0; i<row; ++i){
		if(!isRowClear(i)){
			clear=false;
			break;
		}
	}
	return clear;
}

