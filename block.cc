#include <string>
#include "block.h"
#include "board.h"
#include "window.h"
#include <iostream>

using namespace std;

int Block::getScore() const { return score;}

int Block::getRow() const {
	return row;
}

int Block::getCol() const{
	return col;
}

bool Block::isValid( int r, int c ) const {
	if (r == -1 && c == -1) return true;
	return (0 <= r && r < board.getRow() 
		&& 0 <= c && c < board.getCol());
}

bool Block::canOccupy(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3) const {
	return isValid(r,c) && isValid(r1,c1) && isValid(r2,c2) && isValid(r3,c3)
			&& board.isEmpty(r,c,r1,c1,r2,c2,r3,c3);
}

std::vector<int> Block::getInfo(char type) const{
	vector<int> info;
	if (type == 'I'){
		for(const auto x : {row, col, row, col+1, row, col+2, row, col+3}){
    		info.emplace_back(x);
		}
	} else if (type == 'J'){
		for(const auto x : {row, col, row-1, col, row, col+1, row, col+2}){
    		info.emplace_back(x);
		}
	} else if (type == 'L'){
		for(const auto x : {row, col, row, col+1, row, col+2, row-1, col+2}){
    		info.emplace_back(x);
		}
	} else if (type == 'O'){
		for(const auto x : {row, col, row-1, col, row-1, col+1, row, col+1}){
    		info.emplace_back(x);
    }

	} else if (type == 'T'){
		for(const auto x : {row-1, col, row-1, col+1, row-1, col+2, row, col+1}){
    		info.emplace_back(x);
		}

	} else if (type == 'S'){
		for(const auto x : {row, col, row, col+1, row-1, col+1, row-1, col+2}){
    		info.emplace_back(x);
		}
	} else if (type == 'Z'){
		for(const auto x : {row-1, col, row-1, col+1, row, col+1, row, col+2}){
    		info.emplace_back(x);
		}
  	} else {
		for(const auto x : {row, col}){
	    	info.emplace_back(x);
	    }
  	}
  	cerr << "Returned " << type << endl;
  	for (int i = 0; i < 8; i++){
  		cerr << info[i] << endl;
  	}
  	return info;
}

Block::Block( Board& b, int s, int time ):
	board{b}, score{s}, timeStamp{time} { }

Block::~Block() { }

bool Block::isDropped() const { return dropped; }

void Block::setCoord( int m, int n ) {
	row = m;
	col = n;
}

void Block::moveRight_helper(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3){
	board.setBlock(r,c, r1,c1, r2,c2, r3,c3, nullptr);
	board.setBlock(r,c+1, r1,c1+1, r2,c2+1, r3,c3+1, board.getCurrent());
	++col;
}


void Block::moveLeft_helper(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3){
	board.setBlock(r,c, r1,c1, r2,c2, r3,c3, nullptr);
	board.setBlock(r,c-1, r1,c1-1, r2,c2-1, r3,c3-1, board.getCurrent());
	--col;
}

void Block::moveDown_helper(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3){
	board.setBlock(r,c, r1,c1, r2,c2, r3,c3, nullptr);
	board.setBlock(r+1,c, r1+1,c1, r2+1,c2, r3+1,c3, board.getCurrent());
	++row;
	if (!canOccupy(row+1, c, row+1, c1, row+1, c2, row+1, c3)) dropped = true;
	if (board.isRowFilled(row)) board.deleteRows(row);
}

void Block::drop_helper(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3, int i){
	board.setBlock(r,c, r1,c1, r2,c2, r3,c3, nullptr);
	board.setBlock(r+i,c, r1+i,c1, r2+i,c2, r3+i,c3, board.getCurrent());
	row += i;
	dropped = true;
	if (board.isRowFilled(row)) {
		int rows = board.deleteRows(row);
		for(int i=0; i<rows; ++i) board.dropBlocks(row);
	} 
}

void Block::drop_helper( int r, int c, int i, shared_ptr<Block> b ){
	board.setBlock(r,c, nullptr);
	board.setBlock(r+i,c, b);
	row += i;
	dropped = true;
	if (board.isRowFilled(row)) {
		board.deleteRows(row);
		board.dropBlocks(row);
	}
}




Block_I::Block_I( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_I::~Block_I() { }


vector<int> Block_I::getInfo() const {
	vector<int> info;
	if (form == form1){
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
	if (form == form1 && canOccupy(row+1,col, row+1,col+1, row+2,col+2, row+3,col+3)) 
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




Block_J::Block_J( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_J::~Block_J() { }

vector<int> Block_J::getInfo() const {
	vector<int> info;
	if (form == form1){
		for(const auto x : {row, col, row-1, col, row, col+1, row, col+2}){
    		info.emplace_back(x);
		}
	} else if (form == form2) {
		for(const auto x : {row, col, row-1, col, row-2, col, row-2, col+1}){
    		info.emplace_back(x);
		}
	} else if (form == form3) {
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




Block_L::Block_L( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_L::~Block_L() { }


vector<int> Block_L::getInfo() const {
	vector<int> info;
	if (form == form1){
		for(const auto x : {row, col, row, col+1, row, col+2, row-1, col+2}){
    		info.emplace_back(x);
		}
	} else if (form == form2) {
		for(const auto x : {row, col, row-1, col, row-2, col, row, col+1}){
    		info.emplace_back(x);
		}
	} else if (form == form3) {
		for(const auto x : {row, col, row-1, col, row-1, col+1, row-1, col+2}){
    		info.emplace_back(x);
    	}
	} else {
		for(const auto x : {row-2, col, row-2, col+1, row-1, col+1, row, col+1}){
    		info.emplace_back(x);
    	}
	}
	return info;
}


void Block_L::moveRight(){
	if (form == form2 && canOccupy(row,col+2, row-1,col+1, row-2,col+1))
		moveRight_helper(row,col, row-1,col, row-2,col, row,col+1);
	if (form == form3 && canOccupy(row-2,col+3, row,col+1)) 
		moveRight_helper(row-1,col, row-1,col+1, row-1,col+2, row,col);
	if (form == form4 && canOccupy(row-2,col+2, row-1,col+2, row,col+2)) 
		moveRight_helper(row-2,col, row-2,col+1, row-1,col+1, row,col+1);
	if (form == form1 && canOccupy(row-1,col+3, row,col+3))
		moveRight_helper(row,col, row,col+1, row,col+2, row-1,col+2);
}

void Block_L::moveLeft(){
	if (form == form2 && canOccupy(row,col-1, row-1,col-1, row-2,col-1)) 
		moveLeft_helper(row,col, row-1,col, row-2,col, row,col+1);
	if (form == form3 && canOccupy(row,col-1, row-1,col-1)) 
		moveLeft_helper(row-1,col, row-1,col+1, row-1,col+2, row,col);
	if (form == form4 && canOccupy(row,col, row-1,col, row-2,col-1)) 
		moveLeft_helper(row-2,col, row-2,col+1, row-1,col+1, row,col+1);
	if (form == form1 && canOccupy(row,col-1, row-1,col+1)) 
		moveLeft_helper(row,col, row,col+1, row,col+2, row-1,col+2);
}

void Block_L::moveDown(){
	if (form == form2 && canOccupy(row+1,col, row+1,col+1)) 
		moveDown_helper(row,col, row-1,col, row-2,col, row,col+1);
	if (form == form3 && canOccupy(row+1,col, row,col+1, row,col+2)) 
		moveDown_helper(row-1,col, row-1,col+1, row-1,col+2, row,col);
	if (form == form4 && canOccupy(row-1,col, row+1,col+1)) 
		moveDown_helper(row-2,col, row-2,col+1, row-1,col+1, row,col+1);
	if (form == form1 && canOccupy(row+1,col, row+1,col+1, row+1,col+2))
		moveDown_helper(row,col, row,col+1, row,col+2, row-1,col+2);
}

void Block_L::drop(){
	int i=1;
	if (form == form2) {
		while(canOccupy(row+i,col, row+i,col+1)) { ++i; }
		drop_helper(row,col, row-1,col, row-2,col, row,col+1, i-1);
	}
	if (form == form3) {
		while(canOccupy(row+i,col, row-1+i,col+1, row-1+i,col+2)) { ++i; }
		drop_helper(row-1,col, row-1,col+1, row-1,col+2, row,col, i-1);
	}
	if (form == form4) {
		while(canOccupy(row-2+i,col, row+i,col+1)) { ++i; }
		drop_helper(row-2,col, row-2,col+1, row-1,col+1, row,col+1, i-1);
	}
	if (form == form1) {
		while(canOccupy(row+i,col, row+i,col+1, row+i,col+2)) { ++i; }
		drop_helper(row,col, row,col+1, row,col+2, row-1,col+2, i-1);
	}
}




void Block_L::rotateCW() {
	///---
	if (form == form1) {
		if (canOccupy(row-2,col, row-1,col)) {
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+2, nullptr);
			board.setBlock(row,col, row-1,col, row-2,col, row,col+1, board.getCurrent());
			form = form2;
	  	} else return;
	} else if (form == form2){
		if (canOccupy(row-1,col+1, row-1,col+2)) {
			board.setBlock(row,col, row-1,col, row-2,col, row,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col, board.getCurrent());
			form = form3;
		} else return;
	} else if (form == form3){
		if (canOccupy(row-2,col, row-2,col+1, row,col+1)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col, nullptr);
			board.setBlock(row-2,col, row-2,col+1, row-1,col+1, row,col+1, board.getCurrent());
			form = form4;
		} else return;
	} else{
		if (canOccupy(row,col, row,col+2, row-1,col+2)) {
			board.setBlock(row-2,col, row-2,col+1, row-1,col+1, row,col+1, nullptr);
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+2, board.getCurrent());
			form = form1;
		} else return;
	}
}

void Block_L::rotateCC() {
	if (form == form4) {
		if (canOccupy(row-1,col, row,col, row-1,col+2)) {
			board.setBlock(row-2,col, row-2,col+1, row-1,col+1, row,col+1, nullptr);
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col, board.getCurrent());
			form = form3;
		} else return;
	} else if (form == form3){
		if (canOccupy(row-2,col, row,col+1)) {
			board.setBlock(row-1,col, row-1,col+1, row-1,col+2, row,col, nullptr);
			board.setBlock(row,col, row-1,col, row-2,col, row,col+1, board.getCurrent());
			form = form2;
		} else return;
	} else if (form == form2){
		if (canOccupy(row,col+2, row-1,col+2)) {
			board.setBlock(row,col, row-1,col, row-2,col, row,col+1, nullptr);
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+2, board.getCurrent());
			form = form1;
		} else return;
	} else{
		if (canOccupy(row-2,col, row-2,col+1, row-1,col+1)) {
			board.setBlock(row,col, row,col+1, row,col+2, row-1,col+2, nullptr);
			board.setBlock(row-2,col, row-2,col+1, row-1,col+1, row,col+1, board.getCurrent());
			form = form4;
		} 
	}
}

char Block_L::getType() const { return 'L'; }

string Block_L::drawBlock() const { return "  L\nLLL"; }

void Block_L::drawBlock(Xwindow &x) const {
	x.fillRectangle(445,40,19,19,Xwindow::Orange);
	for(int i=0; i<3; ++i) x.fillRectangle(405+i*20,60,19,19,Xwindow::Orange);
}




Block_O::Block_O( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_O::~Block_O() { }

vector<int> Block_O::getInfo() const {
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




Block_S::Block_S( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_S::~Block_S() { }

vector<int> Block_S::getInfo() const {
	vector<int> info;
	if (form == form1){
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




Block_Z::Block_Z( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_Z::~Block_Z() { }

vector<int> Block_Z::getInfo() const {
	vector<int> info;
	if (form == form1){
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




Block_T::Block_T( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_T::~Block_T() { }

vector<int> Block_T::getInfo() const {
	vector<int> info;
	if (form == form1){
		for(const auto x : {row-1, col, row-1, col+1, row-1, col+2, row, col+1}){
    		info.emplace_back(x);
		}
	} else if (form == form2) {
		for(const auto x : {row-1, col, row, col+1, row-1, col+1, row-2, col+1}){
    		info.emplace_back(x);
		}
	} else if (form == form3) {
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




Block_X::Block_X( Board& b, int s, int time ):
	Block(b, s, time) {
	setCoord(3,5);
}

Block_X::~Block_X() { 
}

vector<int> Block_X::getInfo() const {
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