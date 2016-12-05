#include "block.h"
#include "block_s.h"
#include "board.h"
#include "window.h"
using namespace std;


Block_S::Block_S( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_S::~Block_S() { }

vector<int> Block_S::getInfo( int f ) const {
	vector<int> info;
	if (f == form1){
		for(const auto x : {row, col, row, col+1, row-1, col+1, row-1, col+2}){
    		info.emplace_back(x);
		}
	} else {
		for(const auto x : {row-1, col, row-2, col, row-1, col+1, row, col+1}){
    		info.emplace_back(x);
		}
	}
	return info;
}

void Block_S::moveRight(){
	if (form == form1 && canOccupy(row-1,col+3, row, col+2)) 
		moveRight_helper(row,col, row,col+1, row-1,col+1, row-1,col+2);
	if (form == form2 && canOccupy(row-2,col+1, row-1,col+2, row,col+2))
		moveRight_helper(row-2,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_S::moveLeft(){
	if (form == form1 && canOccupy(row-1,col, row, col-1))
		moveLeft_helper(row,col, row,col+1, row-1,col+1, row-1,col+2);
	if (form == form2 && canOccupy(row-2,col-1, row-1,col-1, row,col)) 
		moveLeft_helper(row-2,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_S::moveDown(){
	if (form == form1 && canOccupy(row+1,col, row+1,col+1, row,col+2)) 
		moveDown_helper(row,col, row,col+1, row-1,col+1, row-1,col+2);
	if (form == form2 && canOccupy(row,col, row+1,col+1)) 
		moveDown_helper(row-2,col, row-1,col, row-1,col+1, row,col+1);
}

void Block_S::drop(){
	int i=1;
	if (form == form1) {
		while(canOccupy(row+i,col, row+i,col+1, row-1+i,col+2)) { ++i; }
		drop_helper(row,col, row,col+1, row-1,col+1, row-1,col+2, i-1);
	}
	if (form == form2) {
		while(canOccupy(row-1+i,col, row+i,col+1)) { ++i; }
		drop_helper(row-2,col, row-1,col, row-1,col+1, row,col+1, i-1);
	}
}

void Block_S::rotateCW() {
	if (form == form1) {
		if (canOccupy(row-1,col, row-2,col)) {
			board.setBlock(row,col, row,col+1, row-1,col+1, row-1,col+2, nullptr);
			board.setBlock(row-2,col, row-1,col, row-1,col+1, row,col+1, board.getCurrent());
			form = form2;
		} else return;
	} else{
		if (canOccupy(row,col, row-1,col+2)) {
			board.setBlock(row-2,col, row-1,col, row-1,col+1, row,col+1, nullptr);
			board.setBlock(row,col, row,col+1, row-1,col+1, row-1,col+2, board.getCurrent());
			form = form1;
		}
	}
}

void Block_S::rotateCC() { rotateCW(); }

char Block_S::getType() const { return 'S'; }

string Block_S::drawBlock() const { return " SS\nSS"; }

void Block_S::drawBlock(Xwindow &x) const {
	for(int i=0; i<2; ++i) x.fillRectangle(425+i*20,40,19,19,Xwindow::Green);
    for(int i=0; i<2; ++i) x.fillRectangle(405+i*20,60,19,19,Xwindow::Green);
}

