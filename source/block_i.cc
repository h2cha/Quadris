#include "block.h"
#include "block_i.h"
#include "board.h"
#include "window.h"
using namespace std;

Block_I::Block_I( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_I::~Block_I() { }


vector<int> Block_I::getInfo( int f ) const {
	vector<int> info;
	if (f == form1){
		for(const auto x : {row, col, row, col+1, row, col+2, row, col+3}){
    		info.emplace_back(x);
		}
	} else { 
		for(const auto x : {row, col, row-1, col, row-2, col, row-3, col}){
    		info.emplace_back(x);
		}
	}
	return info;
}

void Block_I::moveRight(){
	if (form == form1 && canOccupy(row,col+4, -1,-1)) 
		moveRight_helper(row,col, row,col+1, row,col+2, row,col+3);
	if (form == form2 && canOccupy(row,col+1, row-1,col+1, row-2,col+1, row-3,col+1)) 
		moveRight_helper(row,col, row-1,col, row-2,col, row-3,col);
}

void Block_I::moveLeft(){
	if (form == form1 && canOccupy(row,col-1, -1,-1)) 
		moveLeft_helper(row,col, row,col+1, row,col+2, row,col+3);
	if (form == form2 && canOccupy(row,col-1, row-1,col-1, row-2,col-1, row-3,col-1)) 
		moveLeft_helper(row,col, row-1,col, row-2,col, row-3,col);
}

void Block_I::moveDown(){
	if (form == form1 && canOccupy(row+1,col, row+1,col+1, row+1,col+2, row+1,col+3)) 
		moveDown_helper(row,col, row,col+1, row,col+2, row,col+3);
	if (form == form2 && canOccupy(row+1,col, -1, -1))
		moveDown_helper(row,col, row-1,col, row-2,col, row-3,col);
}

void Block_I::drop(){
	int i=1;
	if (form == form1) {
		while(canOccupy(row+i,col, row+i,col+1, row+i, col+2, row+i,col+3)) { ++i; }
		drop_helper(row,col, row,col+1, row,col+2, row,col+3, i-1);
	}
	if (form == form2) {
		while(canOccupy(row+i,col, -1,-1)) { ++i; }
		drop_helper(row,col, row-1,col, row-2,col, row-3,col, i-1);
	}
}


void Block_I::rotateCW() {
	if (form == form1) {
		if (canOccupy(row-1,col, row-2,col, row-3,col)) {
			board.setBlock(row,col, row,col+1, row,col+2, row,col+3, nullptr);
			board.setBlock(row,col, row-1,col, row-2,col, row-3,col, board.getCurrent());
			form = form2;
		} else return;
	} else {
		if (canOccupy(row,col+1, row,col+2, row,col+3)) {
			board.setBlock(row,col, row-1,col, row-2,col, row-3,col, nullptr);
			board.setBlock(row,col, row,col+1, row,col+2, row,col+3, board.getCurrent());
			form = form1;
		} else return;
	}
}

void Block_I::rotateCC() { rotateCW(); };

char Block_I::getType() const { return 'I'; } 

string Block_I::drawBlock() const { return "IIII"; }

void Block_I::drawBlock(Xwindow &x) const {
	for(int i=0; i < 4; ++i) x.fillRectangle(405+i*20,40, 19,19,Xwindow::Cyan);
}
