#include <string>
#include "block.h"
#include "board.h"

using namespace std;

bool Block::isValid( int x, int y ) {
	return (0 <= x && x <= board->getRow() 
		&& 0 <= y && y <= board->getCol());
}


Block::Block( shared_ptr<Board> b, int s, int time ):
	board{b}, score{s}, timeStamp{time} { }

Block::~Block() { board->addScore(score); }

bool Block::isDropped() const { return dropped; }

void Block::setCoord( int m, int n ) {
	r = m;
	c = n;
}


Block_I::Block_I( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_I::~Block_I() { }

void Block_I::rotateCW() {
	if (form == form1) {
		if (isClear(x, y, x, y-1, x, y-2, x, y-3) && isValid(x, y-3)) {
			board->setBlock(x, y-1, this);
			board->setBlock(x, y-2, this);
			board->setBlock(x, y-3, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+3, y, nullptr);
			form = form2;
		} else return;
	} else {
		if (isClear(x, y, x+1, y, x+2, y, x+3, y) && isValid(x+3, y)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x+3, y, this);
			board->setBlock(x, y-1, nullptr);
			board->setBlock(x, y-2, nullptr);
			board->setBlock(x, y-3, nullptr);
			form = form1;
		} else return;
	}
}

void Block_I::rotateCC() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x, y+2, x, y+3) && isValid(x, y+3)){
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x, y+3, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+3, y, nullptr);
			form == form2;
		} else return;
	} else{
		if (isClear(x, y, x-1, y, x-2, y, x-3, y) && isValid(x, y+3)){
			board->setBlock(x-1, y, this);
			board->setBlock(x-2, y, this);
			board->setBlock(x-3, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x, y+3, nullptr);
			form == form1;
		}
	}
}

char Block_I::getType() const { return 'I'; } 

string Block_I::drawBlock() const { return "IIII"; }





Block_J::Block_J( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_J::~Block_J() { }

void Block_J::moveRight(){
	if (form == form1) {
		if (isClear(x+1, y, x+2, y, x+2, y+1, x+2, y+2) && isValid(x+2, y+2)) {
			board->setBlock(x+2, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x+1, y, x+1, y+1, x+2, y, x+3, y) && isValid(x+3, y)) {
			board->setBlock(x+3, y, this);
			board->setBlock(x+1, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
		}
	} else if (form == form3){
		if (isClear(x+1, y, x+1, y+1, x+1, y+2, x+2,y+2) && isValid(x+2, y+2)){
			board->setBlock(x+1, y, this);
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+2, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else{
		if (isClear(x+1, y+1, x+2, y+1, x+3, y+1, x+3,y) && isValid(x+3, y)){
			board->setBlock(x+3, y, this);
			board->setBlock(x+3, y+1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
		}
	}
}

void Block_J::moveLeft(){
	if (form == form1) {
		if (isClear(x-1, y, x, y, x, y+1, x, y+2) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x-1, y, x-1, y+1, x, y, x+1, y) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x-1, y+1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
		}
	} else if (form == form3){
		if (isClear(x-1, y, x-1, y+1, x-1, y+2, x, y+2) && isValid(x-1, y)){
			board->setBlock(x-1, y, this);
			board->setBlock(x-1, y+1, this);
			board->setBlock(x-1, y+2, this);
			board->setBlock(x+1, y+2, nullptr);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
		}
	} else{
		if (isClear(x-1, y+1, x, y+1, x+1, y+1, x+1,y) && isValid(x-1, y+1)){
			board->setBlock(x-1, y+1, this);
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_J::moveDown(){
	if (form == form1) {
		if (isClear(x, y-1, x+1, y-1, x+1, y, x+1, y+1) && isValid(x, y-1)) {
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x, y-1, x, y, x+1, y-1, x+2, y-1) && isValid(x, y-1)) {
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x+2, y-1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y, nullptr);
		}
	} else if (form == form3){
		if (isClear(x, y-1, x, y, x, y+1, x+1, y+1) && isValid(x, y-1)){
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y+1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	} else{
		if (isClear(x, y, x+1, y, x+2, y, x+2, y-1) && isValid(x+2, y-1)){
			board->setBlock(x, y, this);
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y-1, nullptr);
			board->setBlock(x, y+1, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_J::rotateCW() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y, x, y+1, x, y+2, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y+1, x+1, y+1, x+2, y+1, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form4;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y, this);
			board->setBlock(x+1, y, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form1;
		}
	}
}

void Block_J::rotateCC() {
	if (form == form4) {
		if (isClear(x, y, x, y+1, x, y+2, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y, x, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)){
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form1;
		} else return;
	} else{
		if (isClear(x, y+1, x+1, y+1, x+2, y+1, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form4;
		}
	}

}


char Block_J::getType() const { return 'J'; }

string Block_J::drawBlock() const { return "J\nJJJ"; }




Block_L::Block_L( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_L::~Block_L() { }

void Block_L::moveRight(){
	if (form == form1) {
		if (isClear(x+1, y, x+1, y+1, x+1, y+2, x+2, y) && isValid(x+2,y)) {
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x+1, y, x+1, y+1, x+2, y+1, x+3, y+1) && isValid(x+3,y+1)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+3, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
		}
	} else if (form == form3){
		if (isClear(x+1, y+2, x+2, y+2, x+2, y+1, x+2, y) && isValid(x+2,y+2)){
			board->setBlock(x+2, y+2, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y, nullptr);
		}
	} else{
		if (isClear(x+1,y, x+2, y, x+3, y, x+3, y+1) && isValid(x+3,y+1)){
			board->setBlock(x+3, y, this);
			board->setBlock(x+3, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_L::moveLeft(){
	if (form == form1) {
		if (isClear(x-1, y, x-1, y+1, x-1, y+2, x, y) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x-1, y+1, this);
			board->setBlock(x-1, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x-1, y, x-1, y+1, x, y+1, x+1, y+1) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x-1, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	} else if (form == form3){
		if (isClear(x-1, y+2, x, y+2, x, y+1, x,y) && isValid(x-1, y+2)){
			board->setBlock(x, y, this);
			board->setBlock(x, y+1, this);
			board->setBlock(x-2, y+2, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			board->setBlock(x+1, y, nullptr);
		}
	} else{
		if (isClear(x-1, y, x, y, x+1, y, x+1,y+1) && isValid(x-1, y)){
			board->setBlock(x-1, y, this);
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_L::moveDown(){
	if (form == form1) {
		if (isClear(x, y-1, x, y, x, y+1, x+1, y-1) && isValid(x+1, y-1)) {
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y, nullptr);
		}
	} else if (form == form2){
		if (isClear(x, y-1, x, y, x+1, y, x+2, y) && isValid(x, y-1)) {
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	} else if (form == form3){
		if (isClear(x, y+1, x+1, y+1, x+1, y, x+1, y-1) && isValid(x+1, y-1)){
			board->setBlock(x, y+1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	} else{
		if (isClear(x, y-1, x+1, y-1, x+2, y-1, x+2,y) && isValid(x, y-1)){
			board->setBlock(x, y-1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x+1, y-1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_L::rotateCW() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x+1, y+1, x+2, y+2) && isValid(x+2, y+1)) {
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y+2, x+1, y+2, x+1, y+1, x+1, y) && isValid(x+1, y+2)) {
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y, x+1, y, x+2, y, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			form = form4;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x, y+1, x, y+2) && isValid(x, y+2)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form1;
		}
	}
}

void Block_L::rotateCC() {
	if (form == form4) {
		if (isClear(x, y+2, x+1, y+2, x+1, y+1, x+1, y) && isValid(x+1, y+2)) {
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y, x, y+1, x+1, y+1, x+2, y+2) && isValid(x+2, y+1)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			board->setBlock(x+1, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y, x+1, y, x, y+1, x, y+2) && isValid(x, y+2)) {
			board->setBlock(x, y+2, this);
			board->setBlock(x+1,, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form1;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x+2, y, x+2, y+1) && isValid(x+2, y+1)){
			board->setBlock(x+2, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
			form = form4;
		}
	}
}

char Block_L::getType() const { return 'L'; }

string Block_L::drawBlock() const { return "  L\nLLL"; }




Block_O::Block_O( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_O::~Block_O() { }

char Block_O::getType() const { return 'O'; }

string Block_O::drawBlock() const { return "OO\nOO"; }




Block_S::Block_S( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_S::~Block_S() { }

void Block_S::rotateCW() {
	if (form == form1) {
		if (isClear(x, y+2, x, y+1, x+1, y+1, x+1, y) && isValid(x, y+2)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x+1, y+1, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_S::rotateCC() {
	if (form == form1) {
		if (isClear(x, y+2, x, y+1, x+1, y+1, x+1, y) && isValid(x, y+2)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x+1, y+1, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
			form = form1;
		}
	}
}

char Block_S::getType() const { return 'S'; }

string Block_S::drawBlock() const { return " SS\nSS"; }




Block_Z::Block_Z( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_Z::~Block_Z() { }

void Block_Z::rotateCW() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x++2, y, nullptr);
			form = form2;
		} else return;
	} else{
		if (isClear(x, y+1, x+1, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_Z::rotateCC() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x++2, y, nullptr);
			form = form2;
		} else return;
	} else{
		if (isClear(x, y+1, x+1, y+1, x+1, y, x+2, y) && isValid(x+2, y)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

char Block_Z::getType() const { return 'Z'; }

string Block_Z::drawBlock() const { return "ZZ\n ZZ"; }




Block_T::Block_T( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) { }

Block_T::~Block_T() { }

void Block_T::moveRight(){
	if (form == form1) {
		if (isClear(x+1, y, x+2, y, x+2, y+1, x+3, y) && isValid(x+3, y)) {
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+3, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+1, nullptr);
		}
	} else if (form == form2){
		if (isClear(x+1, y, x+1, y+1, x+1, y+2, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else if (form == form3){
		if (isClear(x+1, y+1, x+2, y+1, x+2, y, x+3, y+1) && isValid(x+3, y+1)){
			board->setBlock(x+3, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+1, y, nullptr);
		}
	} else{
		if (isClear(x+1, y+1, x+2, y, x+2, y+1, x+2, y+2) && isValid(x+2, y+2)){
			board->setBlock(x+2, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+1, y+2, nullptr);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x, y+1, nullptr);
		}
	}
}

void Block_T::moveLeft(){
	if (form == form1) {
		if (isClear(x-1, y, x, y, x, y+1, x+1, y) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x, y+1, this);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+2, y, nullptr);
		}
	} else if (form == form2){
		if (isClear(x-1, y, x-1, y+1, x-1, y+2, x, y+1) && isValid(x-1, y)) {
			board->setBlock(x-1, y, this);
			board->setBlock(x-1, y+1, this);
			board->setBlock(x-1, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else if (form == form3){
		if (isClear(x-1, y+1, x, y+1, x, y, x+1, y+1) && isValid(x-1, y+1)){
			board->setBlock(x-1, y+1, this);
			board->setBlock(x, y, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	} else{
		if (isClear(x-1, y+1, x, y, x, y+1, x, y+2) && isValid(x-1, y+1)){
			board->setBlock(x-1, y+1, this);
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
		}
	}
}

void Block_T::moveDown(){
	if (form == form1) {
		if (isClear(x, y-1, x+1, y-1, x+1, y, x+2, y-1) && isValid(x, y-1)) {
			board->setBlock(x+1, y+1, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		}
	} else if (form == form2){
		if (isClear(x, y-1, x, y, x, y+1, x+1, y) && isValid(x, y-1)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+3, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+1, nullptr);
		}
	} else if (form == form3){
		if (isClear(x, y, x+1, y, x+1, y-1, x+2, y) && isValid(x+1, y-1)){
			board->setBlock(x+2, y+2, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+2, nullptr);
			board->setBlock(x+1, y+1, nullptr);
			board->setBlock(x+1, y, nullptr);
		}
	} else{
		if (isClear(x, y, x+1, y-1, x+1, y, x+1, y+1) && isValid(x+1, y-1)){
			board->setBlock(x+3, y, this);
			board->setBlock(x+3, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
		}
	}
}

void Block_T::rotateCW() {
	if (form == form1) {
		if (isClear(x, y, x, y+1, x+1, y+1, x, y+2) && isValid(x, y+2)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y+1, x+1, y+1, x+1, y, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y+1, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x, y+2, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y+1, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x+1, y+2, this);
			board->setBlock(x+2, y+1, nullptr);
			form = form4;
		} else return;
	} else{
		if (isClear(x, y, x+1, y, x+2, y, x+1, y+1) && isValid(x+2, y)) {
			board->setBlock(x, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x+1, y+2, nullptr);
			form = form1;
		}
	}
}

void Block_T::rotateCC() {
	if (form == form4) {
		if (isClear(x, y+1, x+1, y+1, x+1, y, x+2, y+1) && isValid(x+2, y+1)) {
			board->setBlock(x+2, y+1, this);
			board->setBlock(x+1, y+2, nullptr);
			form = form3;
		} else return;
	} else if (form == form3){
		if (isClear(x, y, x, y+1, x+1, y+1, x, y+2) && isValid(x, y+2)) {
			board->setBlock(x, y, this);
			board->setBlock(x, y+2, this);
			board->setBlock(x+1, y, nullptr);
			board->setBlock(x+2, y+1, nullptr);
			form = form2;
		} else return;
	} else if (form == form2){
		if (isClear(x, y, x+1, y, x+2, y, x+1, y+1) && isValid(x+2, y))  {
			board->setBlock(x+1, y, this);
			board->setBlock(x+2, y, this);
			board->setBlock(x, y+1, nullptr);
			board->setBlock(x, y+2, nullptr);
		} else return;
	} else{
		if (isClear(x, y+1, x+1, y, x+1, y+1, x+1, y+2) && isValid(x+1, y+2)) {
			board->setBlock(x, y+1, this);
			board->setBlock(x+1, y+2, this);
			board->setBlock(x, y, nullptr);
			board->setBlock(x+2, y, nullptr);
			form = form4;
		}
	}
}

char Block_T::getType() const { return 'T'; }

string Block_T::drawBlock() const { return "TTT\n T"; }




Block_X::Block_X( shared_ptr<Board> b, int s, int time ):
	Block(b, s, time) {
	setCoord(3,5);
}

Block_X::~Block_X() { }

char Block_X::getType() const { return 'X'; }

string Block_X::drawBlock() const { return "X"; }
