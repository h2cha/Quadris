#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <string>
#include <memory>

class Board;

class Block {
protected:
  Board& board;
  int score;
  int timeStamp;
	int y=3, x=0;
	bool dropped;
	int form;
  
  public:
  	enum { form1=0, form2, form3, form4 };
  	Block( Board& b, int s, int time );
  	virtual ~Block();
    int getScore() const;
    bool isDropped() const;
    bool isEmpty(int n, int m) const;
    bool isEmpty(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3) const;
    void setCoord( int m, int n );
    void moveRight_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3);
    void moveLeft_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3);
    void moveDown_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3);
    void drop_helper(int n, int m, int n1, int m1, int n2, int m2, int n3, int m3);
    void drop_helper(int n, int m);
    virtual void moveRight()=0;
    virtual void moveLeft()=0;
    virtual void moveDown()=0;
    virtual void drop()=0;
    virtual void rotateCW()=0;
    virtual void rotateCC()=0;
  	virtual char getType() const =0;
  	virtual std::string drawBlock() const =0;
    bool isValid(int x, int y) const;
};

class Block_I: public Block {
  public:
  	Block_I( Board& b, int s, int time );
  	~Block_I();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_J: public Block {
  public:
  	Block_J( Board& b, int s, int time );
  	~Block_J();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_L: public Block {
  public:
  	Block_L( Board& b, int s, int time );
  	~Block_L();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};





class Block_O: public Block {
  public:
  	Block_O( Board& b, int s, int time );
  	~Block_O();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};



class Block_S: public Block {
  public:
  	Block_S( Board& b, int s, int time );
  	~Block_S();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_Z: public Block {
  public:
  	Block_Z( Board& b, int s, int time );
  	~Block_Z();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_T: public Block {
  public:
  	Block_T( Board& b, int s, int time );
  	~Block_T();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_X: public Block {
  public:
  	Block_X( Board& b, int s, int time );
  	~Block_X();
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void drop() override;
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};

#endif
