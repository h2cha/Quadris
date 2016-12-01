#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <string>
#include <memory>

class Board;

class Block {
  std::shared_ptr<Board> board;
  int score;
  int timeStamp;
	int r=3, c=0;
	bool dropped;
	int form;
  
  public:
  	enum { form1=0, form2, form3, form4 };
  	Block( std::shared_ptr<Board> b, int s, int time );
  	virtual ~Block();
    bool isDropped() const;
    void setCoord( int m, int n );
    virtual void rotateCW()=0;
    virtual void rotateCC()=0;
  	virtual char getType() const =0;
  	virtual std::string drawBlock() const =0;
};

class Block_I: public Block {
  public:
  	Block_I( std::shared_ptr<Board> b, int s, int time );
  	~Block_I();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_J: public Block {
  public:
  	Block_J( std::shared_ptr<Board> b, int s, int time );
  	~Block_J();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_L: public Block {
  public:
  	Block_L( std::shared_ptr<Board> b, int s, int time );
  	~Block_L();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};





class Block_O: public Block {
  public:
  	Block_O( std::shared_ptr<Board> b, int s, int time );
  	~Block_O();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};



class Block_S: public Block {
  public:
  	Block_S( std::shared_ptr<Board> b, int s, int time );
  	~Block_S();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_Z: public Block {
  public:
  	Block_Z( std::shared_ptr<Board> b, int s, int time );
  	~Block_Z();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_T: public Block {
  public:
  	Block_T( std::shared_ptr<Board> b, int s, int time );
  	~Block_T();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};




class Block_X: public Block {
  public:
  	Block_X( std::shared_ptr<Board> b, int s, int time );
  	~Block_X();
    void rotateCW() override;
    void rotateCC() override;
  	char getType() const override;
  	std::string drawBlock() const override;
};

#endif
