#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <vector>
#include "view.h"
class TextDisplay: public View {
	int level;
	int row, col;
	int score, hiScore;
	std::vector<std::vector<char>> board;
	std::string next;
  public:
  	TextDisplay( int level=0, int row=18, int col=11, int sc=0, int hisc=0 );
  	~TextDisplay();
	void notify( const Cell &c ) override;
	void notify( const Block &b ) override;
	void notify( const Board &b ) override;

	friend std::ostream &operator<<( std::ostream &out, const TextDisplay &td );
};

#endif


