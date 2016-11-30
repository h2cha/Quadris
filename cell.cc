#include "cell.h"
using namespace std;


Cell::Cell( int r, int c ): row{r}, col{c} { }

Cell::~Cell() { }

void Cell::setBlock( const shared_ptr<Block> b ) { 
	block = b;
	notifyViews();
}


int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

char Cell::getType() const { 
	if (block) return block->getType();
	else return ' '; 
}

void Cell::attach( const shared_ptr<View> disp ) { 
	displays.emplace_back(disp); 
}

void Cell::notifyViews() const { 
	for(auto o : displays) o->notify(*this); }

bool Cell::isEmpty() const { return block==nullptr? true : false; }
