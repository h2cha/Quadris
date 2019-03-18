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
  std::vector<std::shared_ptr<View>> views;
  std::shared_ptr<Level> level;
	std::shared_ptr<Block> current;
	std::shared_ptr<Block> theNext;
  std::shared_ptr<Block> hint;
  
  void drawCurrent(std::vector<int> info);
  void drawCurrent( char type, std::shared_ptr<Block> b );
  void popBlock();
  void deleteARow( int r );
  void clearBoard();
	
  public:
  	Board( int r=18, int c=11, int sc=0, int hisc=0 );
  	~Board();
    
    // OPERATIONS
    void createCurrent();
    void createCurrent( char type );
    void createNext();
    void createNext( char type );
    void replaceCurrent( char type ); 
    void moveRight();
    void moveLeft();
    void moveDown();
    void rotateCW();
    void rotateCC();
    void drop();
    void setLevel( int l );
    void levelUp();
    void levelDown();
    int deleteRows( int r );
    void dropBlocks( int r );
    void setSeed(int s );
    void restart();


    // MUTATOR
  	void attachView( const std::shared_ptr<View> v );
    void setBlock( int r, int c, const std::shared_ptr<Block> b );
    void setBlock( int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4, const std::shared_ptr<Block> b );
    void addScore( int n );
    void setScore( int n );
    void setHiScore( int n );

    // ACCESSOR
    int getLevel() const;
    int getRow() const;
    int getCol() const;
    int getScore() const;
    int getHiScore() const;
    std::shared_ptr<Block> getCurrent() const;

    // Checking functions
    bool isEmpty( int x, int y ) const;
    bool isEmpty( int x1, int y1, int x2, int y2, int x3=-1, int y3=-1, int x4=-1, int y4=-1 ) const;
    bool isRowFilled(int r);
    bool checkifLost();

    // notify
    void notifyViews() const;
    void notifyViews( const Block &b ) const;
};
#endif

