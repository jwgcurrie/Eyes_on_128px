/*********************************************************************

  This program is for a 128x128 size display using SPi to communicate
  5 pins are required to interface 
  SH1107 is used here with Arduino mega
*********************************************************************/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


//#define OLED_MOSI     10
//#define OLED_CLK      8
//#define OLED_DC       7
//#define OLED_CS       5
//#define OLED_RST      9

#define mosi_pin 51
#define sclk_pin 52
#define dc_pin 8
#define rst_pin 9
#define cs_pin 53

#define pot A0


// Create the OLED display
Adafruit_SH1107 display = Adafruit_SH1107(128, 128, mosi_pin, sclk_pin, dc_pin, rst_pin, cs_pin);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


void setup()   {
  Serial.begin(9600);

  //display.setContrast (0); // dim display
  // Start OLED
  display.begin(0, true); // we dont use the i2c address but we will reset!


  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();

  // Clear the buffer.
  display.clearDisplay();


}


void loop() {
  int input = analogRead(pot);

  input = input/28;
  Serial.println(input);

  set_eyes(26, 79, input);

  


}

void set_eyes(int L_pupil_x0, int R_pupil_x0, int d_x)
{
      // Left eye
    int L_eye_x0 = display.width() * 0.125;
    int L_eye_y0 = (display.height() - 50)/2;
    int eye_width = 50;
    int eye_height = 50;
    int eye_radius = 20;

    display.drawRoundRect(L_eye_x0, L_eye_y0, eye_width, eye_height, eye_radius, SH110X_WHITE);
    // Pupil
    L_pupil_x0 = L_pupil_x0 + d_x;
    int L_pupil_y0 = 49;
    int pupil_radius = 10;
    display.fillCircle(L_pupil_x0, L_pupil_y0, pupil_radius, SH110X_WHITE);

    
    // Right eye
    int R_eye_x0 = 64;
    int R_eye_y0 = L_eye_y0;

    display.drawRoundRect(R_eye_x0, R_eye_y0, eye_width, eye_height, eye_radius, SH110X_WHITE);
    // Pupil
    R_pupil_x0 = R_pupil_x0 + d_x;
    int R_pupil_y0 = 49;
    display.fillCircle(R_pupil_x0, R_pupil_y0, pupil_radius, SH110X_WHITE);
    
    display.display();
    display.clearDisplay();

}
