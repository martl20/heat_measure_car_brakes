#include <SparkFunMLX90614.h>

#include <SPI.h>   // Default library
#include <Wire.h>   // Default library
#include <Adafruit_GFX.h> // downloaded with Arduino IDE managed libraries
#include <Adafruit_SSD1306.h> // downloaded with Arduino IDE managed libraries
#include <Adafruit_MLX90614.h> // Modified library downloaded from https://www.instructables.com/Multiple-IR-Temperature-Sensors/

#define leftTemp 0x5A
#define rightTemp 0x5C // modified the address on linux with a Raspberry Pi programmer kit. check: https://olegkutkov.me/2017/08/10/mlx90614-raspberry/
float lTemp;
float rTemp;
int ledon = 0;
int ledoff = 1;
int goproon = 0;
int goprooff = 1;
String escstatus;
String GoPROstatus;
String buttonstatus;
String buttonaction;
Adafruit_MLX90614 mlx;

float getLeftTemp(){
  mlx.AddrSet(leftTemp);
  return mlx.readObjectTempC();
}

float getRightTemp(){
  mlx.AddrSet(rightTemp);
  return mlx.readObjectTempC();
}


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/* #define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
*/

unsigned long value = 0UL;
unsigned long middleValue = 16UL; //1/10 seconden
unsigned long maxValue = 160UL; //1 seconden

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);       // LED
  pinMode(PIN_A1, INPUT_PULLUP); // Pushbutton
  pinMode(PIN_A0, INPUT_PULLUP); // Pushbutton
// MLX90614 thermal heat sensor
  if (!Serial){
    Serial.println("Sparkfun MLX90614 test");
}
  mlx.begin();

  // Oled aansturing 128x32
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();

  // Clear the buffer
  display.clearDisplay();



  // Invert and restore display, pausing in-between
  display.invertDisplay(true);

}

void loop() {
  lTemp = getLeftTemp();
  rTemp = getRightTemp();
  if (lTemp >= 500) {lTemp = 0;}
  if (rTemp >= 500) {rTemp = 0;}
   if(value == 0)
  {
  testdrawstylesbase(); 
  }

  if(value == middleValue)
  {
  testdrawstylesbase(); 
  }

  if(value++ >= maxValue)
  {
   serialprintlines();
   value = 0UL;
  }
 // ESC (de)activate 
  if ( digitalRead(PIN_A1) == LOW ) { //Button is pressed?
    if ( ledon == 0 ) {
    digitalWrite(LED_BUILTIN, HIGH);   // LED on
    Serial.println("LED on!!");
    escstatus = "on"  ;
    ledon = 1 ; 
    buttonaction = "ESC";
    buttonstatus = "on";
    } 
  }
  if ( digitalRead(PIN_A1) == HIGH ) { //Button is depressed?
     if ( ledon == 1 ) { ledoff = 0 ; ledon = 2;}
     if ( ledoff == 1 ) { ledon = 0 ;}
  }
  if ( digitalRead(PIN_A1) == LOW ) { //Button is pressed?
    if ( ledoff == 0 ) {
    digitalWrite(LED_BUILTIN, LOW);  // LED off
    Serial.println("LED Off!!");
    escstatus = "off" ;
    ledoff = 1 ; 
    buttonaction = "ESC";
    buttonstatus = "off";
    }
  }
// GoPro (de)Activate
  if ( digitalRead(PIN_A0) == LOW ) { //Button is pressed?
    if ( goproon == 0 ) {
    digitalWrite(LED_BUILTIN, HIGH);   // LED on
    Serial.println("GoPro on!!");
    GoPROstatus = "on"  ;
    goproon = 1 ; 
    buttonaction = "GoPro";
    buttonstatus = "on";
    } 
  }
  if ( digitalRead(PIN_A0) == HIGH ) { //Button is depressed?
     if ( goproon == 1 ) { goprooff = 0 ; goproon = 2;}
     if ( goprooff == 1 ) { goproon = 0 ;}
  }
  if ( digitalRead(PIN_A0) == LOW ) { //Button is pressed?
    if ( goprooff == 0 ) {
    digitalWrite(LED_BUILTIN, LOW);  // LED off
    Serial.println("LED Off!!");
    GoPROstatus = "off" ;
    goprooff = 1 ;
    buttonaction = "GoPro";
    buttonstatus = "off"; 
    }
  }
}


void testdrawstylesbase(void) {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(50,1);             
  display.println(F("Left"));
  display.setCursor(90,1);            
  display.println(F("Right"));
  display.setCursor(0,10);            
  display.println(F("Front"));
  display.setCursor(0,20);            
  display.println(F("Rear"));
  testdrawstylesleft();    // Draw 'stylized' characters
  testdrawstylesright(); 
  testdrawstylesbutton();
  display.display();

}

void testdrawstylesbutton(void) {
  display.setCursor(0,1);             
  display.println(buttonaction);
  display.setCursor(25,1);     
  display.println(buttonstatus);
}

void testdrawstylesleft(void) {
  display.setCursor(48,10);
  display.println(lTemp);
  //Serial1.println("hello");
}

void testdrawstylesright(void) {
  display.setCursor(90,10);     
  display.println(rTemp);
}

void serialprintlines(void) {
  Serial.println("Left: " + String(lTemp) + ", Right: " + String(rTemp));
}


