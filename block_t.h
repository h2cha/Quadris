#ifndef _BLOCK_T_H_
#define _BLOCK_T_H_
#include "block.h"

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
    void drawBlock( Xwindow &x ) const override;
    std::vector<int> getInfo( int f ) const override;
};



#endif


