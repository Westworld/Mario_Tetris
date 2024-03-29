#include "mario_block.h"

//String &Block::_text;

mario_Block::mario_Block(int x, int y) {
  _x = x;
  _y = y;
  _firstY = y;
  _width = 19;
  _height = 19;
}

void mario_Block::idle() {
  if (_state != IDLE) {
    // Serial.println("Block - Idle - Start");

    _lastState = _state;
    _state = IDLE;

    _y = _firstY;
  }
} 

void mario_Block::hit() {
  if (_state != HIT) {
    // Serial.println("Hit - Start");

    _lastState = _state;
    _state = HIT;

    _lastY = _y;

    direction = UP;
  }
}

void mario_Block::setTextBlock() {
  Locator::getDisplay()->setTextColor(0x0000);       
  
  
  if (_text.length() == 1) {
    Locator::getDisplay()->setCursor(_x+6, _y+12);
  }  else {
    Locator::getDisplay()->setCursor(_x+2, _y+12);
  }

  Locator::getDisplay()->print(_text);
}

void mario_Block::setText(String text) {
  _text = text;
}

void mario_Block::init() {
  Locator::getEventBus()->subscribe(this);
  Locator::getDisplay()->drawRGBBitmap(_x, _y, BLOCK, _width, _height);
  setTextBlock();  
}

void mario_Block::update() {

  if (_state == IDLE && _lastState != _state) {
    Locator::getDisplay()->drawRGBBitmap(_x, _y, BLOCK, _width, _height);

    setTextBlock();

    _lastState= _state;

  } else if (_state == HIT) {
    
    if (millis() - lastMillis >= 60) {

      // Serial.print("BLOCK Y = ");
      // Serial.println(_y);
      
      Locator::getDisplay()->fillRect(_x, _y, _width, _height, SKY_COLOR);
      
      _y = _y + (MOVE_PACE * (direction == UP ? -1 : 1));
 
      Locator::getDisplay()->drawRGBBitmap(_x, _y, BLOCK, _width, _height);
      setTextBlock();
                 
      if (floor(_firstY - _y) >= MAX_MOVE_HEIGHT) {
        // Serial.println("DOWN");
        direction = DOWN;
      }

      if (_y >= _firstY && direction == DOWN) {
        idle();
      }

      lastMillis = millis();
    }

  }
}


void mario_Block::execute(EventType event, Sprite* caller) {
  //Serial.println("Checking collision");

  if (event == EventType::MOVE) {
    if (this->collidedWith(caller)) {
      Serial.println("Collision detected");
      hit();
      Locator::getEventBus()->broadcast(EventType::COLLISION, this);
    }
  }
  
}


const char* mario_Block::name() {
  return "BLOCK";
}