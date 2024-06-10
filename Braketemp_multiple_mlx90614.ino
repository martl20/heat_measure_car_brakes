#include <SparkFunMLX90614.h>

#include <SPI.h>   // Default library
#include <Wire.h>   // Default library
#include <Adafruit_GFX.h> // downloaded with Arduino IDE managed libraries
#include <Adafruit_SSD1306.h> // downloaded with Arduino IDE managed libraries
#include <Adafruit_MLX90614.h> // Modified library downloaded from https://www.instructables.com/Multiple-IR-Temperature-Sensors/


#define leftTemp 0x5A
#define rightTemp 0x5C // modified the address on linux with a Raspberry Pi programmer kit. check: https://olegkutkov.me/2017/08/10/mlx90614-raspberry/
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
#define LOGO_HEIGHT   16
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

void setup() {
  Serial.begin(9600);

// MLX90614 thermal heat sensor
 // while (!Serial);
 // Serial.println("Sparkfun MLX90614 test");
  mlx.begin();

  // Oled aansturing 128x32
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //  Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();



  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);

}

void loop() {

 // display.println(getLeftTemp());   display.println(getRightTemp());

  testdrawstylesbase(); 
  testdrawstylesleft();    // Draw 'stylized' characters
  testdrawstylesright(); 
  delay(500);
}



void testdrawstylesbase(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(40,0);             
  display.println(F("Left"));
  display.setCursor(90,0);            
  display.println(F("Right"));
  display.setCursor(0,10);            
  display.println(F("Front"));
  display.setCursor(0,20);            
  display.println(F("Rear"));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.display();
}

void testdrawstylesleft(void) {
  display.setCursor(90,10);
  delay(250);            
  display.println(getLeftTemp());
}

void testdrawstylesright(void) {
  display.setCursor(40,10);     
  delay(250);        // Start at top-left corner
  display.println(getRightTemp());
}

