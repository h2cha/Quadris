#include <iomanip>
#include <iostream>
#include "textdisplay.h"
#include <vector>
#include "cell.h"
#include "block.h"
#include "board.h"
using namespace std;

TextDisplay::TextDisplay( int l, int r, int c, int sc, int hisc ): 
	level{l}, row{r}, col{c}, score{sc}, hiScore{hisc} {
	for(int r=0; r < row; ++r) {
		vector<char> v(col, ' ');
		board.emplace_back(v);
	}
}

TextDisplay::~TextDisplay() { }

void TextDisplay::notify( const Cell &c ) {
	if (c.isEmpty()) board[c.getRow()][c.getCol()] = ' ';
	else board[c.getRow()][c.getCol()] = c.getType();
}

void TextDisplay::notify( const Block &b ) {
	next = b.drawBlock();
}

void TextDisplay::notify( const Board &b ) {
	level = b.getLevel();
	score = b.getScore();
	hiScore = b.getHiScore();
}


ostream &operator<<( ostream &out, const TextDisplay &td ) {
	out << "Level:" << setw(13) << td.level << endl;
	out << "Score:" << setw(13) << td.score << endl;
	out << "Hi Score:" << setw(10) << td.hiScore << endl;
	out << "01234567890" << endl;
	for(int r=0; r < td.row; ++r) {
		for(int c=0; c < td.col; ++c) {
			out << td.board[r][c];
		}
		out << endl;
	}
	out << "01234567890" << endl;
	out << "Next:" << endl;
	out << td.next << endl;

	return out;
}



