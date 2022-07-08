#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

#include "block.h"


#define blocksx 12
#define blocksy 15
#define screenstartx 1
#define screenstarty 1

#define numberblocks 75

class Blocks
{
private:
    Block* allblocks[numberblocks];
    Adafruit_GFX * tft;

public:
    Blocks(Adafruit_GFX * mastertft);
    void Setup(void);
    void Setup(int16_t position, int16_t digit);
    void Setup(byte digit[4]);
    //void update(float ballpos);
    void draw(void);
    void draw(int16_t old_x, int16_t old_y, int16_t loop, int16_t move_x, int16_t move_y);
    void draw(Ball * ball);
    void checkBall(Ball * ball);
    bool checkShot(int16_t x, int16_t y);  
    void drawBlock(int16_t curBlock);
    void findNearestBlock(int16_t &x, int16_t &y, int16_t paddle_x);
    int16_t findNearestBlock(int16_t paddle_x);
    void ClearSurvivingBlocks(int16_t old_x, int16_t old_y);
    void setColor(int16_t thecolor);
};

#endif // BLOCKS_HPP_