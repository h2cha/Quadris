#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <memory>


class Block;
class Board;

class Level {
  public:
  	Level();
  	std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp, char t ) const;
  	virtual std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const =0;
    virtual int getScore() const =0;
  	virtual ~Level()=0;
};

class LevelZero: public Level {
  public:
    LevelZero();
  	~LevelZero();
    std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const override;
    int getScore() const override;
};

class LevelOne: public Level {
  public:
  	LevelOne();
	  std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const override;
	  ~LevelOne();
    int getScore() const override;
};

class LevelTwo: public Level {
  public:
  	LevelTwo();
	  std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const override;
	  ~LevelTwo();
    int getScore() const override;
};

class LevelThree: public Level {
  public:
  	LevelThree();
	  std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const override;
	  ~LevelThree();
    int getScore() const override;
};

class LevelFour: public Level {
  public:
  	LevelFour();
	  std::shared_ptr<Block> createBlock( std::shared_ptr<Board> b, int s, int stamp ) const override;
	  ~LevelFour();
    int getScore() const override;
};

#endif
