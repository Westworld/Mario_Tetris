#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "ball.h"


enum { Arkonoid, Tetris, Space_Invader, Pict_Clock, Pacman };



class Block
{
private:
    int16_t pos_x, pos_y;
    int16_t last_pos_x=0, last_pos_y=0;
    uint16_t color = ILI9486_RED;

public:
    bool active=false;
    bool used=false;

    Block(void);
    void activate(int16_t posx, int16_t posy) ;
    void setUnused(void);
    //void update(float ballpos);;
    void drawPixel(Adafruit_GFX * tft, int16_t x, int16_t y, uint16_t thecolor );
    void draw(Adafruit_GFX * mastertft);
    void drawendofgame(Adafruit_GFX * mastertft, uint16_t newcolor);
    void draw(Adafruit_GFX * mastertft, Ballsize ballsize);
    void draw(Adafruit_GFX * mastertft, int16_t move_x, int16_t move_y);
    void draw(Adafruit_GFX * tft, int16_t move_x, int16_t move_y, int16_t othercolor);
    void undraw(Adafruit_GFX * mastertft);
    void undraw(Adafruit_GFX * mastertft, int16_t move_x, int16_t move_y);
    int16_t check(int16_t posx, int16_t pos_y, int16_t move_x, int16_t move_y, Adafruit_GFX * mastertft);
    bool check(int16_t posx, int16_t posy, Adafruit_GFX * tft);
    bool check(Ballsize ballsize, Ball * ball, Adafruit_GFX * tft);
    bool isNearestBlock(int16_t paddle_x, int16_t &blockx, int16_t &blocky);
    int16_t isNearestBlock(int16_t paddle_x);
    void setColor(int16_t othercolor);
};

void SetGame(int16_t gameType, int16_t screenSize);

#endif // BLOCK_HPP_