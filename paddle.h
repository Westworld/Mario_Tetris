#ifndef PADDLE_HPP_
#define PADDLE_HPP_

#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"
#include "ball.h"

class Paddle
{
private:
    float pos_x;

    int16_t pos_y=63;

    int16_t max_x, max_y;
    const int16_t paddlewidth=2;
    int16_t paddleheight=1;
    uint16_t color = ILI9486_YELLOW;
    bool justLine=true;

    Adafruit_GFX * tft;


public:
    Paddle(Adafruit_GFX  * display);
    void setType(bool gametyp);
    void update(float ballpos);
    void move(int16_t movex);
    void draw(void);
    void undraw(void);
    int16_t getX(void);
    void setX(int16_t x);
};

#endif // PADDLE_HPP_