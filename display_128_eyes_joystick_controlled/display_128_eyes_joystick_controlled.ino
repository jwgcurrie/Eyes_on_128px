/*********************************************************************
  DISPLAY_128_EYES_JOYSTICK
  jwgcurrie
  This program is for a 128x128 size display using SPi to communicate
  5 pins are required to interface 
  SH1107 is used here with Arduino mega.
  
  Abstract eyes are displayed - controlled by a joystick
*********************************************************************/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Display pins on MEGA
#define mosi_pin 51
#define sclk_pin 52
#define dc_pin 8
#define rst_pin 9
#define cs_pin 53

// Joystick Module
#define joy_x A0
#define joy_y A1

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

  int x;
  int y;
  bool x_invert = 0;
  bool y_invert = 1;

void setup()   {
  Serial.begin(9600);

  //display.setContrast (0); // dim display
  // Start OLED
  display.begin(0, true); 


  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();

  // Clear the buffer.
  display.clearDisplay();


  display.print("eyes_joystick_controlled - jwgcurrie");
  display.display();
  display.clearDisplay();

}


void loop() {
  analog_input(joy_x, joy_y, x_invert, y_invert);
  set_eyes(26, 49, x, y);
}


void analog_input(int pin_x, int pin_y, bool x_invert, bool y_invert)
{
  x = analogRead(pin_x);
  y = analogRead(pin_y);

  if(x_invert & y_invert)
  {
    x = 1023 - x;
    y = 1023 - y;
  }
  else if(x_invert)
  {
    x = 1023 - x;
  }
  else if(y_invert)
  {
    y = 1023 - y;
  }

  x = x/28;
  y = y/28;
}

void set_eyes(int pupil_x0, int pupil_y0, int d_x, int d_y)
{
    // Eye characteristics
    int eye_width = 50;
    int eye_height = 50;
    int eye_radius = 20;
    int pupil_radius = 10;

    // Scale joystick readings to pixelspace 
    // Calculate pixelspace limits
    int L_min_x = display.width()/8 + pupil_radius;
    int L_max_x = display.width()/2 - pupil_radius;

    // Left eye
    int L_eye_x0 = display.width()/8;
    int L_eye_y0 = (display.height() - eye_height)/2;
    
    display.drawRoundRect(L_eye_x0, L_eye_y0, eye_width, eye_height, eye_radius, SH110X_WHITE);
    
    // Left pupil
    pupil_x0 = pupil_x0 + d_x;
    pupil_y0 = pupil_y0 + d_y;
    
    display.fillCircle(pupil_x0, pupil_y0, pupil_radius, SH110X_WHITE);

    // Right eye
    int R_eye_x0 = display.width()/2;
    int R_eye_y0 = L_eye_y0;

    display.drawRoundRect(R_eye_x0, R_eye_y0, eye_width, eye_height, eye_radius, SH110X_WHITE);
    // Right Pupil
    pupil_x0 = R_eye_x0 + pupil_radius + d_x;
    display.fillCircle(pupil_x0, pupil_y0, pupil_radius, SH110X_WHITE);
    
    display.display();
    display.clearDisplay();
}

void blink(int pupil_x0, int pupil_y0, int speed)
{

}