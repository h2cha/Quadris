#include "window.h"
#include "graphicsdisplay.h"
#include "cell.h"
#include "block.h"
#include "board.h"
using namespace std;


GraphicsDisplay::GraphicsDisplay( Xwindow &x, int r, int c ):
	window{x}, row{r}, col{c} {

	int yorigin=6, xorigin=100, dimension=27;

	int width=1;
	window.fillRectangle(xorigin, yorigin, dimension*11+width, dimension*18+width, Xwindow::Black);
  	for(int i=0; i<=col; i++){
    	int r = i*dimension + xorigin;
    	window.fillRectangle(r, yorigin, width, dimension*18, Xwindow::White);
  	}
  	for(int i=0; i<=row; i++){
    	int c = i*dimension + yorigin;
    	window.fillRectangle(xorigin, c, dimension*11+width, width, Xwindow::White);
  	}
  	window.fillRectangle(xorigin, 3*dimension + yorigin-0.5 , dimension*11+width, 2, Xwindow::White);
}

GraphicsDisplay::~GraphicsDisplay() { }

void GraphicsDisplay::notify( const Cell &c ) {
}

void GraphicsDisplay::notify( const Block &b ) {

}

void GraphicsDisplay::notify( const Board &b ) {

}

