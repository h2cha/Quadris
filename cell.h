#ifndef _CELL_H_
#define _CELL_H_

#include <memory>
#include <vector>
#include "block.h"
#include "view.h"

class Cell {
	int row, col;
	std::shared_ptr<Block> block;
	std::vector<std::shared_ptr<View>> displays;
  public:
  	Cell( int r=0, int c=0 );
  	~Cell();
  	
    void setBlock( const std::shared_ptr<Block> b );
  	int getRow() const;
  	int getCol() const;
    std::shared_ptr<Block> getBlock() const;
  	char getType() const;
  	void attach( const std::shared_ptr<View> disp );
  	void notifyViews() const;
    bool isEmpty() const;


  	 
};

#endif

