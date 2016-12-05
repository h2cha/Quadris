#include "block.h"
#include "block_o.h"
#include "board.h"
#include "window.h"
using namespace std;


Block_O::Block_O( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_O::~Block_O() { }

vector<int> Block_O::getInfo( int f ) const {
	vector<int> info;
	for(const auto x : {row, col, row-1, col, row-1, col+1, row, col+1}){
    	info.emplace_back(x);
    }
    return info;
}


void Block_O::moveRight(){
	if (canOccupy(row,col+2, row-1,col+2))
		moveRight_helper(row,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_O::moveLeft(){
	if (canOccupy(row,col-1, row-1,col-1)) 
		moveLeft_helper(row,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_O::moveDown(){
	if (canOccupy(row+1,col, row+1,col+1))
		moveDown_helper(row,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_O::drop(){
	int i=1;
	while(canOccupy(row+i,col, row+i,col+1)) { ++i; }
	drop_helper(row,col, row-1,col, row-1,col+1, row,col+1, i-1);
}

void Block_O::rotateCC(){}

void Block_O::rotateCW(){}

char Block_O::getType() const { return 'O'; }

string Block_O::drawBlock() const { return "OO\nOO"; }

void Block_O::drawBlock(Xwindow &x) const {
	for(int i=0; i<2; ++i) x.fillRectangle(405+i*20,40,19,19,Xwindow::Yellow);
	for(int i=0; i<2; ++i) x.fillRectangle(405+i*20,60,19,19,Xwindow::Yellow);
}


