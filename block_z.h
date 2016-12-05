#ifndef _BLOCK_Z_H_
#define _BLOCK_Z_H_
#include "block.h"

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
    void drawBlock( Xwindow &x ) const override;
    std::vector<int> getInfo( int f ) const override;
};



#endif

