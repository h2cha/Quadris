#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <memory>


class Block;
class Board;

class Level {
  protected:
    int seed=0;
    int fallen=0;
  public:
  	Level();

  	std::shared_ptr<Block> createBlock( Board &b, int s, int stamp, char t );
  	virtual std::shared_ptr<Block> createBlock( Board &b, int s, int stamp )=0;
    virtual void rotateCW( Block &b ) const;
    virtual void rotateCC( Block &b ) const;
    virtual void moveRight( Block &b ) const;
    virtual void moveLeft( Block &b ) const;
    virtual void moveDown( Block &b ) const;
    virtual void drop( Block &b );

    int getFallen() const ;
    void setSeed( int s );
    virtual int getScore() const =0;
    virtual int getLevel() const =0;

    void clear();
  	virtual ~Level()=0;
};

class LevelZero: public Level {
  public:
    LevelZero();
  	~LevelZero();
    std::shared_ptr<Block> createBlock( Board &b, int s, int stamp ) override;

    int getScore() const override;
    int getLevel() const override;
    
};

class LevelOne: public Level {
  public:
  	LevelOne();
	  ~LevelOne();

    std::shared_ptr<Block> createBlock( Board &b, int s, int stamp ) override;

    int getScore() const override;
    int getLevel() const override;
};

class LevelTwo: public Level {
  public:
  	LevelTwo();
	  ~LevelTwo();

    std::shared_ptr<Block> createBlock( Board &b, int s, int stamp ) override;

    int getScore() const override;
    int getLevel() const override;

};

class LevelThree: public Level {
  public:
  	LevelThree();
	  ~LevelThree();

    std::shared_ptr<Block> createBlock( Board &b, int s, int stamp ) override;

    void rotateCW( Block &b ) const override;
    void rotateCC( Block &b ) const override;
    void moveRight( Block &b ) const override;
    void moveLeft( Block &b ) const override;
    void moveDown( Block &b ) const override;

    int getScore() const override;
    int getLevel() const override;
};

class LevelFour: public Level {
  public:
  	LevelFour();
	  ~LevelFour();

    std::shared_ptr<Block> createBlock( Board &b, int s, int stamp ) override;
    void drop( Block &b ) override;
    void rotateCW( Block &b ) const override;
    void rotateCC( Block &b ) const override;
    void moveRight( Block &b ) const override;
    void moveLeft( Block &b ) const override;
    void moveDown( Block &b ) const override;

    int getScore() const override;
    int getLevel() const override;
};

#endif

