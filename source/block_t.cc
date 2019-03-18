#include "block.h"
#include "block_t.h"
#include "board.h"
#include "window.h"
using namespace std;


Block_T::Block_T( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_T::~Block_T() { }

vector<int> Block_T::getInfo( int f ) const {
	vector<int> info;
	if (f == form1){
		for(const auto x : {row-1, col, row-1, col+1, row-1, col+2, row, col+1}){
    		info.emplace_back(x);
		}
	} else if (f == form2) {
		for(const auto x : {row-1, col, row, col+1, row-1, col+1, row-2, col+1}){
    		info.emplace_back(x);
		}
	} else if (f == form3) {
		for(const auto x : {row, col, row, col+1, row, col+2, row-1, col+1}){
    		info.emplace_back(x);
    	}
	} else {
		for(const auto x : {row, col, row-1, col, row-2, col, row-1, col+1}){
    		info.emplace_back(x);
    	}
	}
	return info;
}

void Block_T::moveRight(){
	if (form == form3 && canOccupy(row-1,col+2, row,col+3)) 
		moveRight_helper(row,col, row,col+1, row,col+2, row-1,col+1);
	if (form == form4 && canOccupy(row-2,col+1, row-1,col+2, row,col+1))
		moveRight_helper(row-2,col, row-1,col, row,col, row-1,col+1);
	if (form == form1 && canOccupy(row-1, col+3, row,col+2))
		moveRight_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+1);
	if (form == form2 && canOccupy(row-2,col+2, row-1,col+2, row,col+2))
		moveRight_helper(row-2,col+1, row-1,col, row-1,col+1, row,col+1);
}

void Block_T::moveLeft(){
	if (form == form3 && canOccupy(row-1,col, row,col-1))
		moveLeft_helper(row,col, row,col+1, row,col+2, row-1,col+1);
	if (form == form4 && canOccupy(row-2,col-1, row-1,col-1, row,col-1))
		moveLeft_helper(row-2,col, row-1,col, row,col, row-1,col+1);
	if (form == form1 && canOccupy(row-1,col-1, row,col))
		moveLeft_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+1);
	if (form == form2 && canOccupy(row-2,col, row-1,col-1, row,col))
		moveLeft_helper(row-2,col+1, row-1,col, row-1,col+1, row,col+1);
}

void Block_T::moveDown(){
	if (form == form3 && canOccupy(row+1,col, row+1,col+1, row+1,col+2))
		moveDown_helper(row,col, row,col+1, row,col+2, row-1,col+1);
	if (form == form4 && canOccupy(row,col+1, row+1,col))
		moveDown_helper(row-2,col, row-1,col, row,col, row-1,col+1);
	if (form == form1 && canOccupy(row,col, row+1,col+1, row,col+2))
		moveDown_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+1);
	if (form == form2 && canOccupy(row,col, row+1,col+1))
		moveDown_helper(row-2,col+1, row-1,col, row-1,col+1, row,col+1);
}

void Block_T::drop(){
	int i=1;
	if (form == form3) {
		while(canOccupy(row+i,col, row+i,col+1, row+i,col+2)) { ++i; }
		drop_helper(row,col, row,col+1, row,col+2, row-1,col+1, i-1);
	}
	if (form == form4) {
		while(canOccupy(row-1+i,col+1, row+i,col)) { ++i; }
		drop_helper(row-2,col, row-1,col, row,col, row-1,col+1, i-1);
	}
	if (form == form1) {
		while(canOccupy(row-1+i,col, row+i,col+1, row-1+i,col+2)) { ++i; }
		drop_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+1, i-1);
	}
	if (form == form2) {
		while(canOccupy(row-1+i,col, row+i,col+1)) { ++i; }
		drop_helper(row-2,col+1, row-1,col, row-1,col+1, row,col+1, i-1);
	}
}


void Block_T::rotateCW() {
	if (form == form3) {
		if (canOccupy(row-1,col, row-2,col)) {
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+1, nullptr);
			board.setBlock(row-2,col, row-1,col, row,col, row-1,col+1, board.getCurrent());
			form = form4;
		} else return;
	} else if (form == form4){
		if (canOccupy(row,col+1, row-1,col+2)) {
			board.setBlock(row-2,col, row-1,col, row,col, row-1,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+1, board.getCurrent());
			form = form1;
		} else return;
	} else if (form == form1){
		if (canOccupy(row-2,col+1, -1,-1)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+1, nullptr);
			board.setBlock(row-2,col+1, row-1,col, row-1,col+1, row,col+1, board.getCurrent());
			form = form2;
		} else return;
	} else{
		if (canOccupy(row,col, row,col+2)) {
			board.setBlock(row-2,col+1, row-1,col, row-1,col+1, row,col+1, nullptr);
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+1, board.getCurrent());
			form = form3;
		}
	}
}

void Block_T::rotateCC() {
	if (form == form2) {
		if (canOccupy(row-1,col+2, -1,-1)) {
			board.setBlock(row-2,col+1, row-1,col, row-1,col+1, row,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+1, board.getCurrent());
			form = form1;
		} else return;
	} else if (form == form1){
		if (canOccupy(row-2,col, row,col)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+1, nullptr);
			board.setBlock(row-2,col, row-1,col, row,col, row-1,col+1, board.getCurrent());
			form = form4;
		} else return;
	} else if (form == form4){
		if (canOccupy(row,col+1, row,col+2))  {
			board.setBlock(row-2,col, row-1,col, row,col, row-1,col+1, nullptr);
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+1, board.getCurrent());
			form = form3;
		} else return;
	} else{
		if (canOccupy(row-1,col, row-2,col+1)) {
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+1, nullptr);
			board.setBlock(row-2,col+1, row-1,col, row-1,col+1, row,col+1, board.getCurrent());
			form = form2;
		}
	}
}

char Block_T::getType() const { return 'T'; }

string Block_T::drawBlock() const { return "TTT\n T"; }


void Block_T::drawBlock(Xwindow &x) const {
	for(int i=0; i<3; ++i) x.fillRectangle(405+i*20,40,19,19,Xwindow::Brown);
	x.fillRectangle(425,60,19,19,Xwindow::Brown);
}

