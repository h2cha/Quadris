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
  std::vector<std::shared_ptr<Block>> blocks;
  std::shared_ptr<Level> level;
	std::shared_ptr<Block> Current;
	std::shared_ptr<Block> theNext;
	
  public:
  	Board( int l=0, int r=18, int c=11, int sc=0, int hisc=0 );
  	~Board();
    
    // OPERATIONS
    void moveRight();
    void moveLeft();
    void moveDown();
    void rotateCW();
    void rotateCC();
    void drop();


    // MUTATOR
  	void attachView( const std::shared_ptr<View> v );
    void setBlock( int r, int c, const std::shared_ptr<Block> b );
    void addScore( int n );
    void setScore( int n );
    void setHiScore( int n );

    // ACCESSOR
    int getRow() const;
    int getCol() const;
    int getScore() const;
    int getHiScore() const;

    // Checking functions
    bool isEmpty( int x, int y ) const;
    bool isEmpty( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 ) const;
    bool isRowClear(int r);
    bool isAllClear();
    bool checkifLost();
};
#endif

