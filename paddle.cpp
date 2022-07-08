#include "paddle.h"


Paddle::Paddle(Adafruit_GFX  * display)
{
    tft = display;
    pos_x = tftwidth / 2;
    max_x = tftwidth;
    max_y = tftheight;
}

void Paddle::setType(bool gametyp)
{
    justLine = gametyp;
    
}

int16_t Paddle::getX(void) {
    return pos_x;
}

void Paddle::setX(int16_t x) {
    pos_x = x;
}

void Paddle::undraw(void)
{
    int16_t x = pos_x - (paddlewidth/2);
    if (x<0)
        x=0;
    else if (x+paddlewidth > max_x)
            x = max_x-paddlewidth;

    tft->drawPixel(x, pos_y, ILI9486_BLACK);
    tft->drawPixel(x+1, pos_y, ILI9486_BLACK);
}

void Paddle::draw(void)
{
    int16_t x = pos_x - (paddlewidth/2);
    if (x<0)
        x=0;
    else if (x+paddlewidth > max_x)
            x = max_x-paddlewidth;

	tft->drawPixel(x, pos_y, color);
	tft->drawPixel(x+1, pos_y, color);   
}

void Paddle::move(int16_t movex)  // only for block
{

    if (movex == 0) return;

    int16_t x = pos_x - (paddlewidth/2);

    if (x<0)
        x=0;
    else if (x+paddlewidth > max_x)
        x = max_x-paddlewidth;
        
    tft->drawPixel(x, pos_y, ILI9486_BLACK);
    tft->drawPixel(x+1, pos_y, ILI9486_BLACK);    
    pos_x += movex;
    x += movex;
    tft->drawPixel(x, pos_y, color);
    tft->drawPixel(x+1, pos_y, color);
}

void Paddle::update(float ballpos)  // only for justLine
{
	tft->drawPixel(pos_x, pos_y, ILI9486_BLACK);
	tft->drawPixel(pos_x+1, pos_y, ILI9486_BLACK);    


    int16_t half = paddlewidth / 2;
    int16_t old = (uint16_t) pos_x;

    if (ballpos < pos_x) {
        pos_x--;
        if (pos_x - half < 0)
            pos_x = half;
    }
    else {
        pos_x++;
        if (pos_x + half > max_x)
            pos_x = max_x-half;
    }

	tft->drawPixel(pos_x, pos_y, color);
	tft->drawPixel(pos_x+1, pos_y, color);

}