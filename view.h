#ifndef _VIEW_H_
#define _VIEW_H_

class Cell;
class Block;
class Board;

class View {
  public:
	View();
	virtual ~View()=0;
	virtual void notify( const Cell &c )=0;
	virtual void notify( const Block &b )=0;
	virtual void notify( const Board &b )=0;

};

#endif

