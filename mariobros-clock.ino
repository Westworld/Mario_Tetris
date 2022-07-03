// #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"
#include <Ticker.h>
#include "Clockface.h"
#include "DateTime.h"
#include "TetrisMatrixDraw.h"

// #include "WiFiConnect.h"
#include "WiFi.h"
#include <WiFiMulti.h>

#include "../../wifisetting.h"

#define EEPROM_SIZE 512

#define NUM_ROWS 2
#define NUM_COLS 1
#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define PANEL_CHAIN NUM_ROWS*NUM_COLS    // total number of panels chained one to another
#define SERPENT true
#define TOPDOWN true

#define R1_PIN 32
#define G1_PIN 33 //23
#define B1_PIN 23 //33
#define R2_PIN 25
#define G2_PIN 26 // 19
#define B2_PIN 19 // 26
#define A_PIN 27
#define B_PIN 18
#define C_PIN 14
#define D_PIN 17
#define E_PIN -1 // required for 1/32 scan panels, like 64x64. Any available pin would do, i.e. IO32
#define LAT_PIN 16
#define OE_PIN 13
#define CLK_PIN 12

// placeholder for the matrix object
MatrixPanel_I2S_DMA *dma_display_orig = nullptr;

// placeholder for the virtual display object
VirtualMatrixPanel  *dma_display = nullptr;

// WiFiConnect wifi;
byte uhrzeit[6] = {1, 2, 3, 0, 0, 0};

  int16_t old_min  = -1;
  bool old_displaycolon=false;
  bool tetris_still_running=false;
  int16_t currentGame = 1, oldGameSelector = -1;
  
WiFiMulti wifiMulti;
DateTime dateTime;
Clockface *clockface;
const char* wifihostname = "Clockface";

uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

TetrisMatrixDraw * tetris;
//TetrisMatrixDraw tetris(*dma_display);

void displaySetup() {
  HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  HUB75_I2S_CFG mxconfig(
                PANEL_RES_X,   // module width
                PANEL_RES_Y,   // module height
                PANEL_CHAIN,    // chain length
                _pins // pin mapping
  );

 // mxconfig.gpio.e = 18;
 // mxconfig.clkphase = false;

  // Display Setup
  dma_display_orig = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display_orig->setBrightness8(64);
  dma_display_orig->begin();

  // create VirtualDisplay object based on our newly created dma_display object
  dma_display = new VirtualMatrixPanel((*dma_display_orig), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);

  dma_display->clearScreen();
  dma_display->fillScreen(myBLACK);

  dma_display->setRotation(3);
}


void ConnectWifi() {
    WiFi.mode(WIFI_STA);
 
    WiFi.setHostname(wifihostname);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASS);
    wifiMulti.addAP(WIFI_SSID2, WIFI_PASS2); 

    int loop=1;

Serial.println("Connecting Wifi");
    dma_display->setCursor(0, 1);
    dma_display->print("Connecting Wifi...");

    while ((loop < 10) && (wifiMulti.run() != WL_CONNECTED)) {
      dma_display->setCursor(0, loop+1);
      dma_display->print("try again");
      delay(1000);
    }
    if(loop < 10) {
         dma_display->print("connected           ");
         Serial.println("Connected");
    }
    else
    {
           dma_display->setCursor(0, loop+1);
           dma_display->print("NOT CONNECTED ********+");
           dma_display->setCursor(0, loop+2);
           dma_display->print(WIFI_SSID);
           dma_display->setCursor(0, loop+3);
           dma_display->print(WIFI_SSID2);
           delay(5000);
    }
}


void setup() {

  Serial.begin(115200);


  displaySetup();

  tetris = new TetrisMatrixDraw(*dma_display);

  clockface = new Clockface(dma_display);
  
  ConnectWifi();
 
  dateTime.begin();

  GameSelect() ;
  //clockface->setup(&dateTime);
  //InitTetris();
}

void loop() {
  dateTime.update();
  GameSelect();
       
  switch (currentGame) {
      case 1: clockface->update(); break;
      case 2: PlayTetris(); break;
      default: break;
     }
  
  //clockface->update();
  //PlayTetris();

  delay(100);
}

void GameSelect() {
  if( oldGameSelector != (uhrzeit[2] % 2)) {
      oldGameSelector = (uhrzeit[2] % 2);
      if (++currentGame > 2)
        currentGame = 1;

     switch (currentGame) {
      case 1: clockface->setup(&dateTime); break;
      case 2: InitTetris(); break;
      default: break;
     }
  }
}

void InitTetris() {
  // https://githubhot.com/repo/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA/issues/118?page=1
  // matrix->flipDMABuffer();
  dma_display->clearScreen();
    tetris->scale = 2;
  char timeString [8];
  sprintf(timeString, "%d%d:%d%d", uhrzeit[0], uhrzeit[1], uhrzeit[2], uhrzeit[3]);
  tetris->setTime(timeString, true);

  old_min = dateTime.getMinute();
  bool displaycolon = false;
// tetris->drawNumbers(x_pos,y_pos, drawColon, color);
  while(!(tetris->drawNumbers(2,52, displaycolon))) {
    delay(100);
    yield();
    dateTime.update();

    displaycolon = ((uhrzeit[5] % 2) == 1);
    //dma_display->clearScreen();
    dma_display->fillScreen(0);
  }
}

void PlayTetris() {
  if (old_min != dateTime.getMinute()) {
    old_min = dateTime.getMinute();
    char timeString [8];
    sprintf(timeString, "%d%d:%d%d", uhrzeit[0], uhrzeit[1], uhrzeit[2], uhrzeit[3]);
    tetris->setTime(timeString, true);
  }
  
  bool displaycolon = ((uhrzeit[5] % 2) == 1);
  //dma_display->clearScreen();
  if ((displaycolon != old_displaycolon) || (!tetris_still_running)) {
    dma_display->fillScreen(0);
    tetris_still_running = tetris->drawNumbers(2,52, displaycolon);
    old_displaycolon = displaycolon;
  }
}
