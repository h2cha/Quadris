#include "block.h"
#include "block_j.h"
#include "board.h"
#include "window.h"
using namespace std;

Block_J::Block_J( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_J::~Block_J() { }

vector<int> Block_J::getInfo( int f ) const {
	vector<int> info;
	if (f == form1){
		for(const auto x : {row, col, row-1, col, row, col+1, row, col+2}){
    		info.emplace_back(x);
		}
	} else if (f == form2) {
		for(const auto x : {row, col, row-1, col, row-2, col, row-2, col+1}){
    		info.emplace_back(x);
		}
	} else if (f == form3) {
		for(const auto x : {row-1, col, row-1, col+1, row-1, col+2, row, col+2}){
    		info.emplace_back(x);
			}
	} else {
		for(const auto x : {row, col, row, col+1, row-1, col+1, row-2, col+1}){
    		info.emplace_back(x);
    	}
    }
	return info;
}

void Block_J::moveRight(){
	if (form == form4 && canOccupy(row-2,col+2, row-1,col+2, row,col+2))
		moveRight_helper(row,col, row,col+1, row-1,col+1, row-2,col+1);
	if (form == form1 && canOccupy(row-1,col+1, row,col+3)) 
		moveRight_helper(row,col, row-1,col, row,col+1, row,col+2);
	if (form == form2 && canOccupy(row-2,col+2, row-1,col+1, row,col+1))	
		moveRight_helper(row,col, row-1,col, row-2,col, row-2,col+1);
	if (form == form3 && canOccupy(row-1,col+3, row,col+3)) 
		moveRight_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+2);
}

void Block_J::moveLeft(){
	if (form == form4 && canOccupy(row,col-1, row-1,col, row-2,col)) 
		moveLeft_helper(row,col, row,col+1, row-1,col+1, row-2,col+1);
	if (form == form1 && canOccupy(row-1,col-1, row,col-1)) 
		moveLeft_helper(row,col, row-1,col, row,col+1, row,col+2);
	if (form == form2 && canOccupy(row,col-1, row-1,col-1, row-2,col-1)) 
		moveLeft_helper(row,col, row-1,col, row-2,col, row-2,col+1);
	if (form == form3 && canOccupy(row-1,col-1, row,col+1)) 
		moveLeft_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+2);
}

void Block_J::moveDown(){
	if (form == form4 && canOccupy(row+1,col, row+1,col+1)) 
		moveDown_helper(row,col, row,col+1, row-1,col+1, row-2,col+1);
	if (form == form1 && canOccupy(row+1,col, row+1,col+1, row+1,col+2)) 
		moveDown_helper(row,col, row-1,col, row,col+1, row,col+2);
	if (form == form2 && canOccupy(row+1,col, row-1,col+1)) 
		moveDown_helper(row,col, row-1,col, row-2,col, row-2,col+1);
	if (form == form3 && canOccupy(row,col, row,col+1, row+1,col+2)) 
		moveDown_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+2);
}

void Block_J::drop(){
	int i=1;
	if (form == form4) {
		while(canOccupy(row+i,col, row+i,col+1)) { ++i; }
		drop_helper(row,col, row,col+1, row-1,col+1, row-2,col+1, i-1);
	}
	if (form == form1) {
		while(canOccupy(row+i,col, row+i,col+1, row+i, col+2)) { ++i; }
		drop_helper(row,col, row-1,col, row,col+1, row,col+2, i-1);
	}
	if (form == form2) {
		while(canOccupy(row+i,col, row+i-2,col+1)) { ++i; }
		drop_helper(row,col, row-1,col, row-2,col, row-2,col+1, i-1);
	}
	if (form == form3) {
		while(canOccupy(row+i-1,col, row+i-1,col+1, row+i, col+2)) { ++i; }
		drop_helper(row-1,col, row-1,col+1, row-1,col+2, row,col+2, i-1);
	}
}

void Block_J::rotateCW() {
	if (form == form4) {
		if (canOccupy(row-1,col, row,col+2)) {
			board.setBlock(row,col, row,col+1, row-1,col+1, row-2,col+1, nullptr);
			board.setBlock(row,col, row-1,col, row,col+1, row,col+2, board.getCurrent());
			form = form1;
		} else return;
	} else if (form == form1){
		if (canOccupy(row-2,col, row-2,col+1)) {
			board.setBlock(row,col, row-1,col, row,col+1, row,col+2, nullptr);
			board.setBlock(row,col, row-1,col, row-2,col, row-2,col+1, board.getCurrent());
			form = form2;
		} else return;
	} else if (form == form2){
		if (canOccupy(row-1,col+1, row-1,col+2, row,col+2)) {
			board.setBlock(row,col, row-1,col, row-2,col, row-2,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+2, board.getCurrent());
			form = form3;
		} else return;
	} else{
		if (canOccupy(row,col, row,col+1, row-2,col+1)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+2, nullptr);
			board.setBlock(row,col, row,col+1, row-1,col+1, row-2,col+1, board.getCurrent());
			form = form4;
		}
	}
}

void Block_J::rotateCC() {
	if (form == form3) {
		if (canOccupy(row-2,col, row-2,col+1, row,col)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+2, nullptr);
			board.setBlock(row,col, row-1,col, row-2,col, row-2,col+1, board.getCurrent());
			form = form2;
		} else return;
	} else if (form == form2){
		if (canOccupy(row,col+1, row,col+2)) {
			board.setBlock(row,col, row-1,col, row-2,col, row-2,col+1, nullptr);
			board.setBlock(row,col, row-1,col, row,col+1, row,col+2, board.getCurrent());
			form = form1;
		} else return;
	} else if (form == form1){
		if (canOccupy(row-1,col+1, row-2,col+1)){
			board.setBlock(row,col, row-1,col, row,col+1, row,col+2, nullptr);
			board.setBlock(row,col, row,col+1, row-1,col+1, row-2,col+1, board.getCurrent());
			form = form4;
		} else return;
	} else{
		if (canOccupy(row-1,col, row-1,col+2, row,col+2)) {
			board.setBlock(row,col, row,col+1, row-1,col+1, row-2,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col+2, board.getCurrent());
			form = form3;
		}
	}

}


char Block_J::getType() const { return 'J'; }

string Block_J::drawBlock() const { return "J\nJJJ"; }

void Block_J::drawBlock(Xwindow &x) const {
	x.fillRectangle(405,40,19,19,Xwindow::Blue);
	for(int i=0; i<3; ++i) x.fillRectangle(405+i*20,60,19,19,Xwindow::Blue);
}


