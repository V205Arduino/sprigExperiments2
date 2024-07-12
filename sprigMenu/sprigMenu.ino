/*
  TITLE
  By V205
  test
*/

#include <Arduino_GFX_Library.h>

#define WIDTH 160
#define HEIGHT 128
/*
pin stuff, can ignore
GPIO  16 Pin 21 MISO
GPIO 17 pin 22 LITE
GPIO18 pin 24 SCK
GPIO19 pin 25 MOSI
GPIO22 pin 29 D/C
chip select pin, it's gp21/pin27
RESET = gP26
USE THE GP ONE

Arduino_HWSPI(int8_t dc, int8_t cs = GFX_NOT_DEFINED, SPIClass *spi = &SPI, bool is_shared_interface = true); // Constructor thingy
TODO: get
*/

//Arduino_DataBus *bus = new Arduino_HWSPI(16 /* DC */, 5 /* CS */);

Arduino_DataBus *bus = new Arduino_HWSPI(22, 21);
//Arduino_GFX *gfx = new Arduino_ILI9341(bus, 17 /* RST */);
Arduino_GFX *gfx = new Arduino_ST7735(bus, 26, 3);

/*

Arduino_ST7735::Arduino_ST7735(
    Arduino_DataBus *bus, int8_t rst, uint8_t r,
    bool ips, int16_t w, int16_t h,
    uint8_t col_offset1, uint8_t row_offset1, uint8_t col_offset2, uint8_t row_offset2,
*/

// Define pin numbers for the buttons
const int wButtonPin = 5;
const int aButtonPin = 6;
const int sButtonPin = 7;
const int dButtonPin = 8;
const int iButtonPin = 12;
const int jButtonPin = 13;
const int kButtonPin = 14;
const int lButtonPin = 15;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // begin serial comunication.
  delay(1000);
  Serial.println(F("STARTING " __FILE__ " from " __DATE__ __TIME__));


  pinMode(wButtonPin, INPUT_PULLUP);
  pinMode(aButtonPin, INPUT_PULLUP);
  pinMode(sButtonPin, INPUT_PULLUP);
  pinMode(dButtonPin, INPUT_PULLUP);
  pinMode(iButtonPin, INPUT_PULLUP);
  pinMode(jButtonPin, INPUT_PULLUP);
  pinMode(kButtonPin, INPUT_PULLUP);
  pinMode(lButtonPin, INPUT_PULLUP);
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  delay(1000);
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->setCursor(0, 0);
  gfx->setTextColor(GREEN);

  gfx->println(" ");
  gfx->println("Option 1");
  gfx->println("Option 2");
  gfx->println("Option 3");
  gfx->println("Option 4");
  gfx->drawLine(0,0,WIDTH,0,WHITE);
  gfx->drawLine(0,10,WIDTH,10,WHITE);
  for (int i = 0; i < HEIGHT; i += 10) {
    gfx->drawLine(0,i,WIDTH,i,WHITE);
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
