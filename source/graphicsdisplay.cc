#include "window.h"
#include "graphicsdisplay.h"
#include "cell.h"
#include "block.h"
#include "board.h"
using namespace std;


GraphicsDisplay::GraphicsDisplay( Xwindow &x, int r, int c ):
	window{x}, row{r}, col{c} {

	int Rorig=6, Corig=100, dim=27;

	int width=1;
  window.fillRectangle(0,0,500,500,Xwindow::Black);
	window.fillRectangle(Corig, Rorig, dim*11+width, dim*18+width, Xwindow::White);
  	for(int i=0; i<=col; i++){
    	int r = i*dim + Corig;
    	window.fillRectangle(r, Rorig, width, dim*18, Xwindow::Black);
  	}
  	for(int i=0; i<=row; i++){
    	int c = i*dim + Rorig;
    	window.fillRectangle(Corig, c, dim*11+width, width, Xwindow::Black);
  	}

    window.drawString(5,20,"Level:", Xwindow::White);
    window.drawString(5,35,"Score:", Xwindow::White);
    window.drawString(5,50,"HiScore:", Xwindow::White);

    window.drawString(405,20,"Next Block:", Xwindow::White);

}

GraphicsDisplay::~GraphicsDisplay() { }

void GraphicsDisplay::clearNext() {
  window.fillRectangle(405,40,80,40,Xwindow::Black);
}

void GraphicsDisplay::notify( const Cell &c ) {
  int i = c.getRow();
  int j = c.getCol();
  if (c.getType() == 'I') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Cyan);
  if (c.getType() == 'J') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Blue);
  if (c.getType() == 'L') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Orange);
  if (c.getType() == 'O') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Yellow);
  if (c.getType() == 'S') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Green);
  if (c.getType() == 'Z') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Red);
  if (c.getType() == 'T') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Brown);
  if (c.getType() == 'X') 
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Black);
  if (c.getType() == ' ')
    window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::White);
}

void GraphicsDisplay::notify( const Block &b ) {
  clearNext();
  b.drawBlock(window);
}

void GraphicsDisplay::notify( const Board &b ) {
  window.fillRectangle(60,0,40,70,Xwindow::Black); // erase old data
  level = to_string(b.getLevel());
  score = to_string(b.getScore());
  hiScore = to_string(b.getHiScore());
  window.drawString(60,20,level, Xwindow::White);
  window.drawString(60,35,score, Xwindow::White);
  window.drawString(60,50,hiScore, Xwindow::White);
}

