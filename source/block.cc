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

int Block::getForm() const { return form; }

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
  	return info;
}

Block::Block( Board& b, int s, int time ):
	board{b}, score{s}, timeStamp{time} {
	form = form1; 
}

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
}

void Block::drop_helper(int r, int c, int r1, int c1, int r2, int c2, int r3, int c3, int i){
	board.setBlock(r,c, r1,c1, r2,c2, r3,c3, nullptr);
	board.setBlock(r+i,c, r1+i,c1, r2+i,c2, r3+i,c3, board.getCurrent());
	row += i;
	dropped = true;
	for(int i=0; i < 4; ++i) {
		if (board.isRowFilled(row-i)) {
			int rows = board.deleteRows(row-i);
			for(int j=0; j<rows; ++j) board.dropBlocks(row-i);
		} 
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

