#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include "view.h"
#include "window.h"
#include <string>

class Cell;
class Block;
class Board;

class GraphicsDisplay: public View {
  	Xwindow &window;
  	const int row, col;
  	int Corig=100, Rorig=6, dim=27;
  	std::string level, score, hiScore;
 
    void clearNext();
 
  public:
  	GraphicsDisplay( Xwindow &x, int r=18, int c=11 );
  	~GraphicsDisplay() override;

  	void notify( const Cell &c ) override;
  	void notify( const Block &c ) override;
  	void notify( const Board &c ) override;
  	

};


#endif
