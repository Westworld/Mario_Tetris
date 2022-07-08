#ifndef BALL_HPP_
#define BALL_HPP_

#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"

#define int16_t int
#define uint16_t unsigned int

        static const uint16_t tetrisRED = 0xF800;
        static const uint16_t tetrisGREEN = 0x07E0;
        static const uint16_t tetrisBLUE = 0x325F;
        static const uint16_t tetrisWHITE = 0xFFFF;
        static const uint16_t tetrisYELLOW = 0xFF70;
        static const uint16_t tetrisYELLOWlight = 0xFFE0;
        static const uint16_t tetrisCYAN = 0x07FF;
        static const uint16_t tetrisMAGENTA = 0xF81F;
        static const uint16_t tetrisORANGE = 0xFB00;
        static const uint16_t tetrisBLACK = 0x0000;
        
#define ILI9486_YELLOW tetrisYELLOW
#define ILI9486_BLACK tetrisBLACK
#define ILI9486_RED tetrisRED
#define TFT_RED tetrisRED

#define tftwidth 64
#define tftheight 64

struct Ballsize
{
    float x, y, x2, y2;
    float movex, movey;
};

class Ball
{
private:
    float move_x, move_y;
    float pos_x, pos_y;
    int16_t max_x, max_y;
    int16_t speed = 1;
    const int16_t radius=1;
    uint16_t color = ILI9486_YELLOW;
    int16_t blockid = 0;

    Adafruit_GFX * tft;

 

public:
    Ball(Adafruit_GFX * mastertft); //, float speed, float angle);
    void draw(void);
    void undraw(void);
    void move(int16_t x, int16_t y);
    void move_draw(int16_t x, int16_t y);
    int16_t move_draw(void);
    //void move_draw(Blocks * blocks);
    void setAngle(float angle);
    float getAngle();
    int16_t GetX(void);
    void SetY(int16_t y);
    Ballsize GetSize(void);
    void SetBlock(int16_t index);
    void SetMove(float x, float y);
    void InvertMove(bool x, bool y);
};

#endif // BALL_HPP_