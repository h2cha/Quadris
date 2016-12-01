#include "window.h"
#include "graphicsdisplay.h"
#include "cell.h"
#include "block.h"
#include "board.h"
using namespace std;


GraphicsDisplay::GraphicsDisplay( Xwindow &x, int r, int c ):
	window{x}, row{r}, col{c} {
	window.fillRectangle(0, 0, 10, row *50 +20, Xwindow::Black);
	window.fillRectangle(col *50 +10, 0, 10, row *50 +20, Xwindow::Black);
	window.fillRectangle(0, 0, col *50 +20, 10, Xwindow::Black);
	window.fillRectangle(0, row *50 +10, col *5 +20, 10, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() { }

void GraphicsDisplay::notify( const Cell &c ) {
}

void GraphicsDisplay::notify( const Block &b ) {

}

void GraphicsDisplay::notify( const Board &b ) {

}

