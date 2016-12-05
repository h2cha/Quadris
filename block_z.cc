#include "block.h"
#include "block_z.h"
#include "board.h"
#include "window.h"
using namespace std;

Block_Z::Block_Z( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_Z::~Block_Z() { }

vector<int> Block_Z::getInfo( int f ) const {
	vector<int> info;
	if (f == form1){
		for(const auto x : {row-1, col, row-1, col+1, row, col+1, row, col+2}){
    		info.emplace_back(x);
		}
	} else {
		for(const auto x : {row, col, row-1, col, row-1, col+1, row-2, col+1}){
    		info.emplace_back(x);
		}
	}
	return info;
}

void Block_Z::moveRight(){
	if (form == form1 && canOccupy(row-1,col+2, row,col+3)) 
		moveRight_helper(row-1,col, row-1,col+1, row,col+1, row,col+2);
	if (form == form2 && canOccupy(row,col+1, row+1,col)) 
		moveRight_helper(row-2,col+1, row-1,col+1, row-1,col, row,col);
}

void Block_Z::moveLeft(){
	if (form == form1 && canOccupy(row-1,col-1, row,col)) 
		moveLeft_helper(row-1,col, row-1,col+1, row,col+1, row,col+2);
	if (form == form2 && canOccupy(row-2,col, row-1,col-1, row,col-1)) 
		moveLeft_helper(row-2,col+1, row-1,col+1, row-1,col, row,col);
}

void Block_Z::moveDown(){
	if (form == form1 && canOccupy(row,col, row+1,col+1, row+1,col+2))
		moveDown_helper(row-1,col, row-1,col+1, row,col+1, row,col+2);
	if (form == form1 && canOccupy(row,col+1, row+1,col))
		moveDown_helper(row-2,col+1, row-1,col+1, row-1,col, row,col);
}

void Block_Z::drop(){
	int i=1;
	if (form == form1) {
		while(canOccupy(row-1+i,col, row+i,col+1, row+i,col+2)) { ++i; }
		drop_helper(row-1,col, row-1,col+1, row,col+1, row,col+2, i-1);
	}
	if (form == form2) {
		while(canOccupy(row-1+i,col+1, row+i,col)) { ++i; }
		drop_helper(row-2,col+1, row-1,col+1, row-1,col, row,col, i-1);
	} 
}

void Block_Z::rotateCW() {
	if (form == form1) {
		if (canOccupy(row,col, row-2,col+1)) {
			board.setBlock(row-1,col, row-1,col+1, row,col+1, row,col+2, nullptr);
			board.setBlock(row-2,col+1, row-1,col+1, row-1,col, row,col, board.getCurrent());
			form = form2;
		} else return;
	} else{
		if (canOccupy(row,col+1, row,col+2)) {
			board.setBlock(row-2,col+1, row-1,col+1, row-1,col, row,col, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row,col+1, row,col+2, board.getCurrent());
			form = form1;
		}
	}
}

void Block_Z::rotateCC() { rotateCW(); }

char Block_Z::getType() const { return 'Z'; }

string Block_Z::drawBlock() const { return "ZZ\n ZZ"; }

void Block_Z::drawBlock(Xwindow &x) const {
	for(int i=0; i<2; ++i) x.fillRectangle(405+i*20,40,19,19,Xwindow::Red);
        for(int i=0; i<2; ++i) x.fillRectangle(425+i*20,60,19,19,Xwindow::Red);
}


