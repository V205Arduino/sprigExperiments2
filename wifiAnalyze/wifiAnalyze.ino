// Simple WiFi network scanner application
// Released to the public domain in 2022 by Earle F. Philhower, III
#include <WiFi.h>


#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
//#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <BTstackLib.h>

#define TFT_CS 21
#define TFT_RST 26  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 22


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

#define WIDTH 160
#define HEIGHT 128


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



void setup() {
  Serial.begin(115200);

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
  tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
  tft.setCursor(0, 12);
}

const char *macToString(uint8_t mac[6]) {
  static char s[20];
  sprintf(s, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return s;
}

const char *encToString(uint8_t enc) {
  switch (enc) {
    case ENC_TYPE_NONE: return "NONE";
    case ENC_TYPE_TKIP: return "WPA";
    case ENC_TYPE_CCMP: return "WPA2";
    case ENC_TYPE_AUTO: return "AUTO";
  }
  return "UNKN";
}

void loop() {
  delay(5000);
  tft.fillScreen(ST77XX_BLACK);
  Serial.printf("Beginning scan at %lu\n", millis());
  auto cnt = WiFi.scanNetworks();
  if (!cnt) {
    Serial.printf("No networks found\n");
  } else {
    Serial.printf("Found %d networks\n\n", cnt);
    Serial.printf("%32s %5s %17s %2s %4s\n", "SSID", "ENC", "BSSID        ", "CH", "RSSI");
    for (auto i = 0; i < cnt; i++) {
      uint8_t bssid[6];
      WiFi.BSSID(i, bssid);
      Serial.printf("%32s %5s %17s %2d %4ld\n", WiFi.SSID(i), encToString(WiFi.encryptionType(i)), macToString(bssid), WiFi.channel(i), WiFi.RSSI(i));
    }
  }

  Serial.printf("\n--- Sleeping ---\n\n\n");
  delay(5000);

}

// /*
// Experiments with Sprig and Arduino.
// */





// const int wButtonPin = 5;
// const int aButtonPin = 6;
// const int sButtonPin = 7;
// const int dButtonPin = 8;
// const int iButtonPin = 12;
// const int jButtonPin = 13;
// const int kButtonPin = 14;
// const int lButtonPin = 15;




// bool lastWButtonState = false;
// bool wButtonState = false;
// bool lastAButtonState = false;
// bool aButtonState = false;
// bool lastSButtonState = false;
// bool sButtonState = false;
// bool lastDButtonState = false;
// bool dButtonState = false;

// int menuNumber = 1;
// int option = 1;

// int optionLocation = (9 * (option - 1)) + 12 + 3;


// void setup() {
//   Serial.begin(115200);
//   Serial.print(F("Hello! ST77xx TFT Test"));


//   pinMode(wButtonPin, INPUT_PULLUP);
//   pinMode(aButtonPin, INPUT_PULLUP);
//   pinMode(sButtonPin, INPUT_PULLUP);
//   pinMode(dButtonPin, INPUT_PULLUP);
//   pinMode(iButtonPin, INPUT_PULLUP);
//   pinMode(jButtonPin, INPUT_PULLUP);
//   pinMode(kButtonPin, INPUT_PULLUP);
//   pinMode(lButtonPin, INPUT_PULLUP);


//   /*
//   for (int i = 5; i < 9; i++) {
//     pinMode(i, INPUT_PULLUP);
//   }
//   for (int i = 12; i < 16; i++) {
//     pinMode(i, INPUT_PULLUP);
//   }
//   */
//   pinMode(17, OUTPUT);
//   digitalWrite(17, HIGH);
//   // Use this initializer if using a 1.8" TFT screen:
//   tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
//   tft.setRotation(3);

//   //rocket fast sprig, anyone?

//   // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
//   // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
//   // may end up with a black screen some times, or all the time.
//   //15MHz seems to be max SPI speed of ST7735
//   //maximum SPI data rate of RP2040 is around 62.5 Mbps (62.5 MHz).
//   //tft.setSPISpeed(40000000);


//   Serial.println(F("Initialized.."));

//   tft.fillScreen(ST77XX_BLACK);
//   tft.setCursor(0, 0);
//   tft.setTextColor(ST77XX_GREEN);
//   tft.println("TITLE - Page 1 of 1");
//   //tft.drawTriangle(0, 4, 5, 6, 5, 2, ST77XX_YELLOW);
//   tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
//   tft.setCursor(0, 12);

// }


// void loop() {

//   //Serial.println("looping, I guess");
//   if (millis() - timer >= interval) {
//     //Serial.println("interval");
//     timer = millis();
//     // read the pushbutton input pin:
//     wButtonState = digitalRead(wButtonPin);
//     sButtonState = digitalRead(sButtonPin);
//     dButtonState = digitalReadFast(dButtonPin);



//     if (dButtonState != lastDButtonState) {
//       if ((dButtonState == false) ) {

//       }
//     }
//   }
//   lastWButtonState = wButtonState;
//   lastSButtonState = sButtonState;
//   lastDButtonState = dButtonState;
//   lastAButtonState = aButtonState;
// }