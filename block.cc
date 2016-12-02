#include <string>
#include "block.h"
#include "board.h"

using namespace std;

int Block::getScore() const { return score;}

bool Block::isValid( int x, int y ) const {
	return (0 <= x && x <= board.getRow() 
		&& 0 <= y && y <= board.getCol());
}

Block::Block( Board& b, int s, int time ):
	board{b}, score{s}, timeStamp{time} { }

Block::~Block() { board.addScore(score); }

bool Block::isEmpty(int n, int m) const {
	return (isValid(n, m) &&
		board.isEmpty(n, m));
}

bool Block::isEmpty(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3) const {
	return (isValid(n, m, n1, m1, n2, m2, n3, m3) &&
		board.isEmpty(n, m, n1, m1, n2, m2, n3, m3));
}

bool Block::isDropped() const { return dropped; }

void Block::setCoord( int m, int n ) {
	y = m;
	x = n;
}

void Block::moveRight_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3){
	int x = n;
	int y = m;
	int x1 = n1;
	int y1 = m1;
	int x2 = n2;
	int y2 = m2;
	int x3 = n3;
	int y3 = m3;

	if(isEmpty(x+1, y, x1+1, y1, x2+1, y2, x3+1, y3)){
		board.setBlock(x, y, nullptr);
		board.setBlock(x1, y1, nullptr);
		board.setBlock(x2, y2, nullptr);
		board.setBlock(x3, y3, nullptr);

		x += 1;
		x1 += 1;
		x2 += 1;
		x3 += 1;

		board.setBlock(x, y, board.getCurrent());
		board.setBlock(x1, y1, board.getCurrent());
		board.setBlock(x2, y2, board.getCurrent());
		board.setBlock(x3, y3, board.getCurrent());

		this->x +=1;
	}
}

void Block::moveLeft_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3){
	int x = n;
	int y = m;
	int x1 = n1;
	int y1 = m1;
	int x2 = n2;
	int y2 = m2;
	int x3 = n3;
	int y3 = m3;

	if(isEmpty(x-1, y, x1-1, y1, x2-1, y2, x3-1, y3)){
		board.setBlock(x, y, nullptr);
		board.setBlock(x1, y1, nullptr);
		board.setBlock(x2, y2, nullptr);
		board.setBlock(x3, y3, nullptr);

		x -= 1;
		x1 -= 1;
		x2 -= 1;
		x3 -= 1;

		board.setBlock(x, y, board.getCurrent());
		board.setBlock(x1, y1, board.getCurrent());
		board.setBlock(x2, y2, board.getCurrent());
		board.setBlock(x3, y3, board.getCurrent());

		this->x -=1;
	}
}

void Block::moveDown_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3){
	int x = n;
	int y = m;
	int x1 = n1;
	int y1 = m1;
	int x2 = n2;
	int y2 = m2;
	int x3 = n3;
	int y3 = m3;

	if(isEmpty(x, y-1, x1, y1-1, x2, y2-1, x3, y3-1)){
		board.setBlock(x, y, nullptr);
		board.setBlock(x1, y1, nullptr);
		board.setBlock(x2, y2, nullptr);
		board.setBlock(x3, y3, nullptr);

		y -= 1;
		y1 -= 1;
		y2 -= 1;
		y3 -= 1;

		board.setBlock(x, y, board.getCurrent());
		board.setBlock(x1, y1, board.getCurrent());
		board.setBlock(x2, y2, board.getCurrent());
		board.setBlock(x3, y3, board.getCurrent());

		this->y -=1;
	}
}

void Block::drop_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3){
	int x = n;
	int y = m;
	int x1 = n1;
	int y1 = m1;
	int x2 = n2;
	int y2 = m2;
	int x3 = n3;
	int y3 = m3;

	while(isEmpty(x, y-1, x1, y1-1, x2, y2-1, x3, y3-1)){
		board.setBlock(x, y, nullptr);
		board.setBlock(x1, y1, nullptr);
		board.setBlock(x2, y2, nullptr);
		board.setBlock(x3, y3, nullptr);

		y -= 1;
		y1 -= 1;
		y2 -= 1;
		y3 -= 1;

		board.setBlock(x, y, board.getCurrent());
		board.setBlock(x1, y1, board.getCurrent());
		board.setBlock(x2, y2, board.getCurrent());
		board.setBlock(x3, y3, board.getCurrent());

		this->y -=1;
	}
}

void Block::drop_helper(int n, int m){
	int x = n;
	int y = m;

	while(isEmpty(x, y-1)){
		board.setBlock(x, y, nullptr);

		y -= 1;

		board.setBlock(x, y, board.getCurrent());

		this->y -=1;
	}
}




Block_I::Block_I( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_I::~Block_I() { }

void Block_I::moveRight(){
	if (form == form1){
		moveRight_helper(x, y, x+1, y, x+2 , y, x+3, y);
	} else{
		moveRight_helper(x, y, x, y+1, x , y+2, x, y+3);
	}
}

void Block_I::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y, x+1, y, x+2 , y, x+3, y);
	} else{
		moveLeft_helper(x, y, x, y+1, x , y+2, x, y+3);
	}
}

void Block_I::moveDown(){
	if (form == form1){
		moveDown_helper(x, y, x+1, y, x+2 , y, x+3, y);
	} else{
		moveDown_helper(x, y, x, y+1, x , y+2, x, y+3);
	}
}

void Block_I::drop(){
	if (form == form1){
		drop_helper(x, y, x+1, y, x+2 , y, x+3, y);
	} else{
		drop_helper(x, y, x, y+1, x , y+2, x, y+3);
	}
}


void Block_I::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x, y+2, x, y+3) && isValid(x, y-3)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x, y+3, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			board.setBlock(x+3, y, nullptr);
			form = form2;
		} else return;
	} else {
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+3, y) && isValid(x+3, y)) {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x+3, y, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x, y+3, nullptr);
			form = form1;
		} else return;
	}
}

void Block_I::rotateCC() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x, y+2, x, y+3) && isValid(x, y+3)){
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x, y+3, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			board.setBlock(x+3, y, nullptr);
			form = form2;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+3, y) && isValid(x, y+3)){
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x+3, y, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x, y+3, nullptr);
			form = form1;
		}
	}
}

char Block_I::getType() const { return 'I'; } 

string Block_I::drawBlock() const { return "IIII"; }





Block_J::Block_J( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_J::~Block_J() { }

void Block_J::moveRight(){
	if (form == form1){
		moveRight_helper(x, y, x+1, y, x+1 , y+1, x+1, y+2);
	} 
	else if (form == form2){
		moveRight_helper(x, y, x, y+1, x+1 , y, x+2, y);
	}
	else if (form == form3){
		moveRight_helper(x, y, x, y+1, x , y+2, x+1, y+2);
	}
	else{
		moveRight_helper(x, y+1, x+1, y+1, x+2 , y+1, x+2, y);
	}
}

void Block_J::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y, x+1, y, x+1 , y+1, x+1, y+2);
	} 
	else if (form == form2){
		moveLeft_helper(x, y, x, y+1, x+1 , y, x+2, y);
	}
	else if (form == form3){
		moveLeft_helper(x, y, x, y+1, x , y+2, x+1, y+2);
	}
	else{
		moveLeft_helper(x, y+1, x+1, y+1, x+2 , y+1, x+2, y);
	}
}

void Block_J::moveDown(){
	if (form == form1){
		moveDown_helper(x, y, x+1, y, x+1 , y+1, x+1, y+2);
	} 
	else if (form == form2){
		moveDown_helper(x, y, x, y+1, x+1 , y, x+2, y);
	}
	else if (form == form3){
		moveDown_helper(x, y, x, y+1, x , y+2, x+1, y+2);
	}
	else{
		moveDown_helper(x, y+1, x+1, y+1, x+2 , y+1, x+2, y);
	}
}

void Block_J::drop(){
	if (form == form1){
		drop_helper(x, y, x+1, y, x+1 , y+1, x+1, y+2);
	} 
	else if (form == form2){
		drop_helper(x, y, x, y+1, x+1 , y, x+2, y);
	}
	else if (form == form3){
		drop_helper(x, y, x, y+1, x , y+2, x+1, y+2);
	}
	else{
		drop_helper(x, y+1, x+1, y+1, x+2 , y+1, x+2, y);
	}
}

void Block_J::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x+1, y+1, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y, x, y+1, x, y+2, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y+1, x+1, y+1, x+2, y+1, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x+1, y+1, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form4;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form1;
		}
	}
}

void Block_J::rotateCC() {
	if (form == form4) {
		if (board.isEmpty(x, y, x, y+1, x, y+2, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y+1, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y, x, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)){
			board.setBlock(x+1, y+1, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form1;
		} else return;
	} else{
		if (board.isEmpty(x, y+1, x+1, y+1, x+2, y+1, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form4;
		}
	}

}


char Block_J::getType() const { return 'J'; }

string Block_J::drawBlock() const { return "J\nJJJ"; }




Block_L::Block_L( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_L::~Block_L() { }

void Block_L::moveRight(){
	if (form == form1){
		moveRight_helper(x, y, x, y+1, x, y+2, x+1, y);
	} 
	else if (form == form2){
		moveRight_helper(x, y, x, y+1, x+1 , y+1, x+2, y+1);
	}
	else if (form == form3){
		moveRight_helper(x, y+2, x+1, y+2, x+1 , y+1, x+1, y);
	}
	else{
		moveRight_helper(x, y, x+1, y, x+2 , y, x+2, y+1);
	}
}

void Block_L::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y, x, y+1, x, y+2, x+1, y);
	} 
	else if (form == form2){
		moveLeft_helper(x, y, x, y+1, x+1 , y+1, x+2, y+1);
	}
	else if (form == form3){
		moveLeft_helper(x, y+2, x+1, y+2, x+1 , y+1, x+1, y);
	}
	else{
		moveLeft_helper(x, y, x+1, y, x+2 , y, x+2, y+1);
	}
}

void Block_L::moveDown(){
	if (form == form1){
		moveDown_helper(x, y, x, y+1, x, y+2, x+1, y);
	} 
	else if (form == form2){
		moveDown_helper(x, y, x, y+1, x+1 , y+1, x+2, y+1);
	}
	else if (form == form3){
		moveDown_helper(x, y+2, x+1, y+2, x+1 , y+1, x+1, y);
	}
	else{
		moveDown_helper(x, y, x+1, y, x+2 , y, x+2, y+1);
	}
}

void Block_L::drop(){
	if (form == form1){
		drop_helper(x, y, x, y+1, x, y+2, x+1, y);
	} 
	else if (form == form2){
		drop_helper(x, y, x, y+1, x+1 , y+1, x+2, y+1);
	}
	else if (form == form3){
		drop_helper(x, y+2, x+1, y+2, x+1 , y+1, x+1, y);
	}
	else{
		drop_helper(x, y, x+1, y, x+2 , y, x+2, y+1);
	}
}

void Block_L::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x+2, y+2) && isValid(x+2, y+1)) {
			board.setBlock(x+1, y+1, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x+1, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y+2, x+1, y+2, x+1, y+1, x+1, y) && isValid(x+1, y+2)) {
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+2, y+1) && isValid(x+2, y+1)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			board.setBlock(x+1, y+1, nullptr);
			form = form4;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x, y+1, x, y+2) && isValid(x, y+2)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+2, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form1;
		}
	}
}

void Block_L::rotateCC() {
	if (form == form4) {
		if (board.isEmpty(x, y+2, x+1, y+2, x+1, y+1, x+1, y) && isValid(x+1, y+2)) {
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y+1, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x+2, y+2) && isValid(x+2, y+1)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+2, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			board.setBlock(x+1, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y, x+1, y, x, y+1, x, y+2) && isValid(x, y+2)) {
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+1, y+1, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form1;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+2, y+1) && isValid(x+2, y+1)){
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
			form = form4;
		}
	}
}

char Block_L::getType() const { return 'L'; }

string Block_L::drawBlock() const { return "  L\nLLL"; }




Block_O::Block_O( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_O::~Block_O() { }

void Block_O::moveRight(){
	moveRight_helper(x, y, x, y+1, x+1 , y, x+1, y+1);
}

void Block_O::moveLeft(){
	moveLeft_helper(x, y, x, y+1, x+1 , y, x+1, y+1);
}

void Block_O::moveDown(){
	moveDown_helper(x, y, x, y+1, x+1 , y, x+1, y+1);
}

void Block_O::drop(){
	drop_helper(x, y, x, y+1, x+1 , y, x+1, y+1);
}

void Block_O::rotateCC(){}

void Block_O::rotateCW(){}

char Block_O::getType() const { return 'O'; }

string Block_O::drawBlock() const { return "OO\nOO"; }




Block_S::Block_S( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_S::~Block_S() { }

void Block_S::moveRight(){
	if (form == form1){
		moveRight_helper(x, y, x+1, y, x+1 , y+1, x+2, y+1);
	} else{
		moveRight_helper(x, y+2, x, y+1, x+1 , y+1, x+1, y);
	}
}

void Block_S::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y, x+1, y, x+1 , y+1, x+2, y+1);
	} else{
		moveLeft_helper(x, y+2, x, y+1, x+1 , y+1, x+1, y);
	}
}

void Block_S::moveDown(){
	if (form == form1){
		moveDown_helper(x, y, x+1, y, x+1 , y+1, x+2, y+1);
	} else{
		moveDown_helper(x, y+2, x, y+1, x+1 , y+1, x+1, y);
	}
}

void Block_S::drop(){
	if (form == form1){
		drop_helper(x, y, x+1, y, x+1 , y+1, x+2, y+1);
	} else{
		drop_helper(x, y+2, x, y+1, x+1 , y+1, x+1, y);
	}
}

void Block_S::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y+2, x, y+1, x+1, y+1, x+1, y) && isValid(x, y+2)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+1, y+1, x+2, y+1) && isValid(x+2, y+1)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_S::rotateCC() {
	if (form == form1) {
		if (board.isEmpty(x, y+2, x, y+1, x+1, y+1, x+1, y) && isValid(x, y+2)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+1, y+1, x+2, y+1) && isValid(x+2, y+1)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
			form = form1;
		}
	}
}

char Block_S::getType() const { return 'S'; }

string Block_S::drawBlock() const { return " SS\nSS"; }




Block_Z::Block_Z( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_Z::~Block_Z() { }

void Block_Z::moveRight(){
	if (form == form1){
		moveRight_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y);
	} else{
		moveRight_helper(x, y, x, y+1, x+1 , y+1, x+1, y+2);
	}
}

void Block_Z::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y);
	} else{
		moveLeft_helper(x, y, x, y+1, x+1 , y+1, x+1, y+2);
	}
}

void Block_Z::moveDown(){
	if (form == form1){
		moveDown_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y);
	} else{
		moveDown_helper(x, y, x, y+1, x+1 , y+1, x+1, y+2);
	}
}

void Block_Z::drop(){
	if (form == form1){
		drop_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y);
	} else{
		drop_helper(x, y, x, y+1, x+1 , y+1, x+1, y+2);
	}
}

void Block_Z::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form2;
		} else return;
	} else{
		if (board.isEmpty(x, y+1, x+1, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_Z::rotateCC() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form2;
		} else return;
	} else{
		if (board.isEmpty(x, y+1, x+1, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

char Block_Z::getType() const { return 'Z'; }

string Block_Z::drawBlock() const { return "ZZ\n ZZ"; }




Block_T::Block_T( Board& b, int s, int time ):
	Block(b, s, time) { }

Block_T::~Block_T() { }

void Block_T::moveRight(){
	if (form == form1){
		moveRight_helper(x, y, x+1, y, x+1, y+1, x+2, y);
	} 
	else if (form == form2){
		moveRight_helper(x, y, x, y+1, x , y+2, x+1, y+1);
	}
	else if (form == form3){
		moveRight_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y+1);
	}
	else{
		moveRight_helper(x, y+1, x+1, y, x+1 , y+1, x+1, y+2);
	}
}

void Block_T::moveLeft(){
	if (form == form1){
		moveLeft_helper(x, y, x+1, y, x+1, y+1, x+2, y);
	} 
	else if (form == form2){
		moveLeft_helper(x, y, x, y+1, x , y+2, x+1, y+1);
	}
	else if (form == form3){
		moveLeft_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y+1);
	}
	else{
		moveLeft_helper(x, y+1, x+1, y, x+1 , y+1, x+1, y+2);
	}
}

void Block_T::moveDown(){
	if (form == form1){
		moveDown_helper(x, y, x+1, y, x+1, y+1, x+2, y);
	} 
	else if (form == form2){
		moveDown_helper(x, y, x, y+1, x , y+2, x+1, y+1);
	}
	else if (form == form3){
		moveDown_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y+1);
	}
	else{
		moveDown_helper(x, y+1, x+1, y, x+1 , y+1, x+1, y+2);
	}
}

void Block_T::drop(){
	if (form == form1){
		drop_helper(x, y, x+1, y, x+1, y+1, x+2, y);
	} 
	else if (form == form2){
		drop_helper(x, y, x, y+1, x , y+2, x+1, y+1);
	}
	else if (form == form3){
		drop_helper(x, y+1, x+1, y+1, x+1 , y, x+2, y+1);
	}
	else{
		drop_helper(x, y+1, x+1, y, x+1 , y+1, x+1, y+2);
	}
}

void Block_T::rotateCW() {
	if (form == form1) {
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x, y+2) && isValid(x, y+2)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y+1, x+1, y+1, x+1, y, x+2, y+1) && isValid(x+2, y+1)) {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x, y+2, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y+1, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x+2, y+1, nullptr);
			form = form4;
		} else return;
	} else{
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+1, y+1) && isValid(x+2, y)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_T::rotateCC() {
	if (form == form4) {
		if (board.isEmpty(x, y+1, x+1, y+1, x+1, y, x+2, y+1) && isValid(x+2, y+1)) {
			board.setBlock(x+2, y+1, board.getCurrent());
			board.setBlock(x+1, y+2, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (board.isEmpty(x, y, x, y+1, x+1, y+1, x, y+2) && isValid(x, y+2)) {
			board.setBlock(x, y, board.getCurrent());
			board.setBlock(x, y+2, board.getCurrent());
			board.setBlock(x+1, y, nullptr);
			board.setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (board.isEmpty(x, y, x+1, y, x+2, y, x+1, y+1) && isValid(x+2, y))  {
			board.setBlock(x+1, y, board.getCurrent());
			board.setBlock(x+2, y, board.getCurrent());
			board.setBlock(x, y+1, nullptr);
			board.setBlock(x, y+2, nullptr);
		} else return;
	} else{
		if (board.isEmpty(x, y+1, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board.setBlock(x, y+1, board.getCurrent());
			board.setBlock(x+1, y+2, board.getCurrent());
			board.setBlock(x, y, nullptr);
			board.setBlock(x+2, y, nullptr);
			form = form4;
		}
	}
}

char Block_T::getType() const { return 'T'; }

string Block_T::drawBlock() const { return "TTT\n T"; }




Block_X::Block_X( Board& b, int s, int time ):
	Block(b, s, time) {
	setCoord(3,5);
}

Block_X::~Block_X() { 
}
void Block_X::moveRight(){}

void Block_X::moveLeft(){}

void Block_X::moveDown(){}

void Block_X::drop(){
	drop_helper(x, y);
}

void Block_X::rotateCC(){}

void Block_X::rotateCW(){}

char Block_X::getType() const { return 'X'; }

string Block_X::drawBlock() const { return "X"; }
