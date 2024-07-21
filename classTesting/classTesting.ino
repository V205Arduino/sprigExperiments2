/*
  TITLE
  By V205
*/


struct menu  // declare the struct
{
  char title[12];     //Name can only be up to 12 characters long
  char* options[25];  // options could be 25 maybe?
  bool showBackArrow;
};


class menuTesting {
public:
  char title[12];     //Name can only be up to 12 characters long
  char* options[25];  // options could be 25 maybe?
  bool showBackArrow;
  void show() {  
      
  }

  void update(){
    
  }
};

menuTesting mainMenu;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // begin serial comunication.
  delay(1000);
  Serial.println(F("STARTING " __FILE__ " from " __DATE__ __TIME__));

}

void loop() {
  // put your main code here, to run repeatedly:
}
