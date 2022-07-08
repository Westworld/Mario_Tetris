#ifndef SHOT_HPP_
#define SHOT_HPP_

#define tftwidth 64
#define tftheight 64

#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"
#include "ball.h"

/*
        static const uint16_t tetrisRED = 0xF800;
        static const uint16_t tetrisGREEN = 0x07E0;
        static const uint16_t tetrisBLUE = 0x325F;
        static const uint16_t tetrisWHITE = 0xFFFF;
        static const uint16_t tetrisYELLOW = 0xFFE0;
        static const uint16_t tetrisCYAN = 0x07FF;
        static const uint16_t tetrisMAGENTA = 0xF81F;
        static const uint16_t tetrisORANGE = 0xFB00;
        static const uint16_t tetrisBLACK = 0x0000;
        */
        
#define ILI9486_YELLOW tetrisYELLOW
#define TFT_WHITE tetrisWHITE
#define ILI9486_BLACK tetrisBLACK

#define shotwidth 1
#define shotheight 1
#define shotspeed 1

struct Shotsize
{
    float x, y, x2, y2;
    float movey;
};

class Shot
{
private:
    float move_y;
    float pos_x, pos_y;
    int16_t max_x, max_y;
    uint16_t color = ILI9486_YELLOW;
    bool active=false;

    Adafruit_GFX * tft;

 

public:
    Shot(Adafruit_GFX * mastertft, int16_t movex); //, float speed, float angle);
    void draw(void);
    void undraw(void);
    int16_t move_draw(void);
    Shotsize GetSize(void);
    void activate(int16_t posx, int16_t posy, bool down);
    void deactivate(void);
    int16_t getX(void);
    int16_t getY(bool up);

};

#endif // BALL_HPP_