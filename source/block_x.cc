#include "block.h"
#include "block_x.h"
#include "board.h"
#include "window.h"
using namespace std;

Block_X::Block_X( Board& b, int s, int time ):
	Block(b, s, time) {
	setCoord(3,5);
}

Block_X::~Block_X() { 
}

vector<int> Block_X::getInfo( int f ) const {
	vector<int> info;
	for(const auto x : {row, col}){
    	info.emplace_back(x);
    }
    return info;
}

void Block_X::moveRight(){}

void Block_X::moveLeft(){}

void Block_X::moveDown(){}

void Block_X::drop(){
	int i=1;
	while(canOccupy(row+i,col, -1, -1)) { ++i; }
	drop_helper(row, col, i-1, shared_ptr<Block>{this});
}

void Block_X::rotateCC(){}

void Block_X::rotateCW(){}

char Block_X::getType() const { return 'X'; }

string Block_X::drawBlock() const { return "X"; }

void Block_X::drawBlock( Xwindow &x ) const {}




