/*
  TITLE
  By V205
*/


//#include <cstring>  // For strcpy


/*
struct menu  // declare the struct
{
  char title[12];     //Name can only be up to 12 characters long
  char* options[25];  // options could be 25 maybe?
  bool showBackArrow;
};
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



int menuNumber = 1;
int option = 1;

int optionLocation = (9 * (option - 1)) + 12 + 3;



const char* mainOptions[] = {
  "Wii", "Bluetooth", "Other Tools", "Settings", "Device Info", "Shutdown", "another option"
};

class Menu {
public:
  char title[13];     // Increased to 13 to accommodate null terminator
  char* options[25];  // Array of pointers to char
  bool showBackArrow;
  int optionCount;  // Added to keep track of the number of options

  void show() {
    tft.fillScreen(ST77XX_BLACK);

    tft.setCursor(0, 0);

    if (showBackArrow) {
      tft.drawTriangle(0, 4, 5, 6, 5, 2, ST77XX_YELLOW);
      tft.setCursor(10, 0);
    }
    tft.setTextColor(ST77XX_GREEN);
    tft.println(title);
    tft.drawLine(0, 10, WIDTH, 10, ST77XX_WHITE);
    tft.setCursor(0, 12);

    for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
      tft.setCursor(0, 12 + (9 * i));
      tft.println(options[i]);
      tft.drawLine(0, 20 + (9 * i), WIDTH, 20 + (9 * i), ST77XX_WHITE);
    }

    tft.fillTriangle(WIDTH - 3, optionLocation, WIDTH - 7, optionLocation - 2, WIDTH - 7, optionLocation + 2, ST77XX_YELLOW);
  }


  void update() {

  }


  Menu() {
  }

  /*
    Menu(const char* titleInit, char* optionsInit[], int optionCountInit, bool showBackArrowInit)
    {
        strncpy(title, titleInit, 12);
        title[12] = '\0'; // Ensure null-termination
        optionCount = (optionCountInit > 25) ? 25 : optionCountInit;
        for (int i = 0; i < optionCount; i++) {
            options[i] = optionsInit[i];
        }
        showBackArrow = showBackArrowInit;
    }

    
    
    // Disable copy constructor and assignment operator
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    */
};

Menu mainMenu = Menu();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // begin serial comunication.
  delay(1000);
  Serial.println(F("STARTING " __FILE__ " from " __DATE__ __TIME__));
  tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  tft.setRotation(3);
  mainMenu.title = "test";
  mainMenu.options = mainOptions;
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
