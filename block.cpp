#include "Block.h"
#include <Console.h>


// cannot use #define, as size depending of game type
		int16_t blockwidth = 3;
        int16_t blockheight = 4;
        int16_t blockstartx = 64;
        int16_t blockstarty = 30;
        int16_t blockoffset = 2;


Block::Block(void)
{
    used=false;
    active=false;
}

void Block::setColor(int16_t othercolor)
{
    color = othercolor;
}

void Block::activate(int16_t posx, int16_t posy) 
{
    used = true;
    active = true;

    pos_x = posx;
    pos_y = posy;

    //Console::info("Block pos [%d] [%d]: ", pos_x, pos_y);
}

void Block::setUnused(void) 
{
    used = false;
    active = false;
}

void Block::drawPixel(Adafruit_GFX * tft, int16_t x, int16_t y, uint16_t thecolor ) {
        tft->drawPixel(x, y, thecolor);
        tft->drawPixel(x+1, y, thecolor);
        tft->drawPixel(x+2, y, thecolor);
        
        tft->drawPixel(x, y+1, thecolor);
        tft->drawPixel(x+1, y+1, thecolor);
        tft->drawPixel(x+2, y+1, thecolor);
        
        tft->drawPixel(x, y+2, thecolor);
        tft->drawPixel(x+1, y+2, thecolor);
        tft->drawPixel(x+2, y+2, thecolor); 
        
        tft->drawPixel(x, y+3, thecolor);
        tft->drawPixel(x+1, y+3, thecolor);
        tft->drawPixel(x+2, y+3, thecolor); }

void Block::draw(Adafruit_GFX * tft)
{
    int thecolor;
    
    if (used) {
        if (active)
        	thecolor = color;
        else
        	thecolor = tetrisYELLOWlight;
        	
        this->drawPixel(tft, pos_x, pos_y, thecolor);	
               
    } 
}

void Block::drawendofgame(Adafruit_GFX * tft, uint16_t newcolor)
{
    if (used) {
        if (active)
            this->drawPixel(tft, last_pos_x, last_pos_y, newcolor);	
  
    } 
}

void Block::draw(Adafruit_GFX * tft, int16_t move_x, int16_t move_y)
{
    if (used) {
        if (active) {
            this->drawPixel(tft, pos_x+move_x, pos_y+move_y, color);	
            last_pos_x=pos_x+move_x; 
            last_pos_y=pos_y+move_y;
        }    
        else
        {
            this->drawPixel(tft, pos_x+move_x, pos_y+move_y, tetrisMAGENTA);	

        }
            
    } 
}

void Block::draw(Adafruit_GFX * tft, int16_t move_x, int16_t move_y, int16_t othercolor)
{
    if (used) {
        if (active) {
            this->drawPixel(tft, pos_x+move_x, pos_y+move_y, othercolor);	

            last_pos_x=pos_x+move_x; 
            last_pos_y=pos_y+move_y;
        }    
        else
        {
            this->drawPixel(tft, pos_x+move_x, pos_y+move_y, othercolor);	

        }
            
    } 
}

void Block::draw(Adafruit_GFX * tft, Ballsize ballsize)
{
    if (used) {
        if ((ballsize.x < pos_x) && (ballsize.x2 > (pos_x+blockwidth)) 
            && (ballsize.y < pos_y) && (ballsize.y2 > (pos_y+blockheight)) ) {
            
            this->draw(tft);
        }
            
    } 
}

void Block::undraw(Adafruit_GFX * tft)
{
    if (used) {
        this->undraw(tft, 0, 0);  
    } 
}

void Block::undraw(Adafruit_GFX * tft, int16_t move_x, int16_t move_y)
{
    if (used) {
        this->drawPixel(tft, pos_x+move_x, pos_y+move_y, ILI9486_BLACK);	
    } 
}

bool Block::check(Ballsize ballsize, Ball * ball, Adafruit_GFX * tft) {
   bool result=false;
// 0/0 is right bottom
    if (used) {
        /*
                if ( (ballsize.x <= (pos_x+blockwidth)) && (ballsize.x2 >= pos_x) 
            && (ballsize.y <= (pos_y+blockheight)) && (ballsize.y2 >= pos_y) )
            */
        if ( (ballsize.x2 >= (pos_x)) && (ballsize.x <= (pos_x+blockwidth)) 
            && (ballsize.y2 >= (pos_y)) && (ballsize.y <= (pos_y+blockheight)) )
            {
                if (!active) 
                {
                    return true;
                }
                else
                {
                    active=false;
                    undraw(tft);
                    //draw(tft);

                    // if x or x2 is exact on block, dann revert x, else y
                    // going left                                       going right
                    if ((int(ballsize.x) == (pos_x+blockwidth)) || (int(ballsize.x2) == (pos_x))|| ((int(ballsize.x2)+1) == (pos_x)))
                        ball->InvertMove(true,false);
                    else
                        ball->InvertMove(false,true);
                    
                    return true;
                }    
            }       
    }

    return result;

}

int16_t Block::check(int16_t posx, int16_t posy, int16_t movex, int16_t movey, Adafruit_GFX * tft)
{
    int16_t result=false;

    if (used && active) {
        if ( (posx <= (pos_x+blockwidth)) && (posx >= pos_x) 
            && (posy <= (pos_y+blockheight)) && (posy >= pos_y) )
            {
                active=false;
                draw(tft);
                // calculate new reflection angle
                if (movex<0)  // moving left
                {    if (posx <= (pos_x+blockwidth))
                    { result = 1; return result;  }
                }
                else
                {    if (posx >= pos_x)
                    { result = 2; return result;  }
                }

                if (movey<0)  // moving down
                {    if (posy <= (pos_y+blockheight))
                    { result = 3; return result;  }
                }
                else
                {    if (posy >= pos_y)
                    { result = 4; return result;  }
                }   
                return false;  // should never happen! pass thru...             
            }       
    }

    return false;
}



bool Block::check(int16_t posx, int16_t posy, Adafruit_GFX * tft)
{
    int16_t result=false;

    if (used && active) {

        //Console::info("Shotup,%d,%d,%d,%d,%d,%d", posx, posy, last_pos_x, last_pos_x+blockwidth,
        //         last_pos_y,  last_pos_y+blockheight); 
      
        if ( (posx >= (last_pos_x)) && (posx <= last_pos_x+blockwidth) ) {
           
            if ( (posy <= (last_pos_y+blockheight)) && (posy >= last_pos_y) )
            {

                draw(tft, last_pos_x-pos_x, last_pos_y-pos_y, TFT_RED);  // malen nur mit Versatz, woher Versatz erfahren?
                active=false;
                return true;           
            }       
        }
    }
    return false;
}


bool Block::isNearestBlock(int16_t paddle_x, int16_t &blockx, int16_t &blocky) {
    if (used && active) {
        if ( (paddle_x <= (last_pos_x+blockwidth+5)) && (paddle_x >= (last_pos_x-5)) )
            {
                blockx = last_pos_x + (blockwidth/2);
                blocky = last_pos_y;// + blockheight;
                return true;
            }
    }
    return false;
}

int16_t Block::isNearestBlock(int16_t paddle_x) {
    if (used && active) {
        if  (paddle_x < last_pos_x)  return 1;
        if  (paddle_x > (last_pos_x + blockwidth))  return -1;
        return 0;
    }
    return 0;
}


void SetGame(int16_t gameType, int16_t screenSize) {

		 blockwidth = 2;
         blockheight = 2;
         blockstartx = 1;
         blockstarty = 1;
         blockoffset = 1;
         
}

/*
void SetGame(int16_t gameType, int16_t screenSize) {
if (gameType == Arkonoid) {
    if (screenSize == 4) {
        blockwidth = 23;
         blockheight = 20;
         blockstartx = 430;
         blockstarty = 420;
         blockoffset = 10;
    }
    else {  // 2.4 Inch
        blockwidth = 12;
        blockheight = 14;
        blockstartx = 280;
        blockstarty = 400;
        blockoffset = 10;
    }

}
else {  // Space Invader
    if (screenSize == 4) {
         blockwidth = 13;
         blockheight = 12;
         blockstartx = 460;
         blockstarty = 520;
         blockoffset = 5;
    }
    else {  // 2.4 Inch
        blockwidth = 12;
        blockheight = 14;
        blockstartx = 280;
        blockstarty = 400;
        blockoffset = 10;
    }
}

}
*/