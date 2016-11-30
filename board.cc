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

int Board::getScore() const { return score; }

int Board::getHiScore() const { return hiScore; }

void Board::attachView( const shared_ptr<View> v ) {
	for(auto &i : theBoard) {
		for(auto &j : i) j.attach(v);
	}
}

void Board::setBlock( int r, int c, const std::shared_ptr<Block> b ) {
	theBoard[r][c].setBlock(b);
}


//test

