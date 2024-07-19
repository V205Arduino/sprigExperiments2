#include <Arduino.h>


#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
//#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Define the pins for the display
#define TFT_CS 20
#define TFT_RST 26
#define TFT_DC 22
#define TFT_MOSI 19
#define TFT_SCK 18
#define TFT_LED 17

// Define the pins for the LEDs
#define LED_LEFT 4
#define LED_RIGHT 28

// Define the pins for the buttons
#define MC_BUTTON_W 5
#define MC_BUTTON_A 6
#define MC_BUTTON_S 7
#define MC_BUTTON_D 8
#define MC_BUTTON_I 12
#define MC_BUTTON_J 13
#define MC_BUTTON_K 14
#define MC_BUTTON_L 15

class Button {
 public:
  static const int BUTTON_W = 0;
  static const int BUTTON_A = 1;
  static const int BUTTON_S = 2;
  static const int BUTTON_D = 3;
};

class Sprig {
 private:
  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
  int cursor = 0;
  String screen = "main_menu";

 public:
  Sprig() {
    tft.initR(INITR_BLACKTAB); // initialize the display
    pinMode(LED_LEFT, OUTPUT);
    pinMode(LED_RIGHT, OUTPUT);
  }

  void set_title(String title) {
    Serial.print("\x1b]0; " + title + "\x1b\\");
  }

  void reset_display(bool reset_title = true) {
    if (reset_title) {
      set_title("");
    }
    Serial.print("\x1b[2J\x1b[H");
  }

  int poll_input(int button = -1) {
    /*
    while (true) {

      if (keypad.stateChanged) {
        if (keypad.key == button) {
          return;
        } else {
          return keypad.key;
        }
      }
    }
    */
    return 0;
  }

  String selection_screen(String items[], String title = "") {
    if (sizeof(items) > 8) {
      Serial.println("Items exceeds display size");
      return "";
    }

    reset_display();
    if (title != "") {
      set_title(title);
    }

    for (int i = 0; i < sizeof(items); i++) {
      Serial.println("  " + items[i]);
    }

    cursor = 1;
    Serial.print("\x1b[0;0H>");
    while (true) {
      int movement = poll_input();

      if (movement == Button::BUTTON_W) {
        if (cursor == 1) {
          continue;
        } else {
          Serial.print("\x1b[" + String(cursor) + ";0H \r\x1b[" + String(cursor - 1) + ";0H>");
          cursor--;
        }
      } else if (movement == Button::BUTTON_S) {
        if (cursor >= sizeof(items)) {
          continue;
        } else {
          Serial.print("\x1b[" + String(cursor) + ";0H \r\x1b[" + String(cursor + 1) + ";0H>");
          cursor++;
        }
      } else if (movement == Button::BUTTON_D) {
        return items[cursor - 1];
      }
    }
  }
};


Sprig sprig;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Example usage:
  String items[] = { "Item 1", "Item 2", "Item 3" };
  String selected = sprig.selection_screen(items, "Select an item");
  Serial.println("Selected: " + selected);
  delay(1000);
}