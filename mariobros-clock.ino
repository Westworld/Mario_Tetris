// #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"
#include "Clockface.h"
#include "DateTime.h"

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
WiFiMulti wifiMulti;
DateTime dateTime;
Clockface *clockface;
const char* wifihostname = "Clockface";

uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

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
 // EEPROM.begin(EEPROM_SIZE);

  displaySetup();

  clockface = new Clockface(dma_display);

/*
  dma_display->setTextSize(1);
  dma_display->setTextColor(myWHITE);
  dma_display->setCursor(5, 0);
  dma_display->println("CLOCKWISE");
  dma_display->setTextColor(myBLUE);
  dma_display->setCursor(0, 32);
  dma_display->print("connecting...");
  */
  
  ConnectWifi();
 
  dateTime.begin();


  clockface->setup(&dateTime);
}

void loop() {
  clockface->update();
}
