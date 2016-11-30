#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <memory>
#include "cell.h"

class Block;
class TextDisplay;
class GraphicsDisplay;
class Level;

class Board {
	int row, col;
	int score, hiScore;
  std::vector<std::vector<Cell>> theBoard;
  std::shared_ptr<Level> level;
	std::shared_ptr<Block> Current;
	std::shared_ptr<Block> theNext;
	
  public:
  	Board( int l=0, int r=18, int c=11, int sc=0, int hisc=0 );
  	~Board();
    
    void moveRight();
    void moveLeft();
    void rotateCW();
    void rotateCC();
    void drop();

  	void attachView( const std::shared_ptr<View> v );
    void setBlock( int r, int c, const std::shared_ptr<Block> b );
  	int getScore() const;
  	int getHiScore() const;
  	




};
#endif

