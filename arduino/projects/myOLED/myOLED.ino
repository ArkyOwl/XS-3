/*
Program description: my OLED test without third party library.
Author: Andrey Miroshnikov
Date Created: 22/07/12017
Last Updated: 23/07/12017
*/

//Includeds
#include <Wire.h>
//ASCII font
#include "glcdfont.c"

//Defines
#define I2CADDR 0x3C
//Commands
#define SETCONTRAST 0x81
#define DISPLAYALLON_RESUME 0xA4
#define DISPLAYALLON 0xA5
#define NORMALDISPLAY 0xA6
#define INVERTDISPLAY 0xA7
#define DISPLAYOFF 0xAE
#define DISPLAYON 0xAF
#define SETDISPLAYOFFSET 0xD3
#define SETCOMPINS 0xDA
#define SETVCOMDETECT 0xDB
#define SETDISPLAYCLOCKDIV 0xD5
#define SETPRECHARGE 0xD9
#define SETMULTIPLEX 0xA8
#define SETLOWCOLUMN 0x00
#define SETHIGHCOLUMN 0x10
#define SETSTARTLINE 0x40
#define MEMORYMODE 0x20
#define COMSCANINC 0xC0
#define COMSCANDEC 0xC8
#define SEGREMAP 0xA0
#define CHARGEPUMP 0x8D
#define EXTERNALVCC 0x1
#define SWITCHCAPVCC 0x2
//OLED specs
#define LCDWIDTH                  128
#define LCDHEIGHT                 64

//Declarations
static uint8_t buffer[10];
/*
static uint8_t buffer[LCDHEIGHT * LCDWIDTH / 8] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3C,0x3C,
    0x1C,0x1C,0x7C,0xFC,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,
    0xE0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x80,0xE0,0xF0,0xF0,0xF0,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF8,0xFE,0xFF,0x3F,0x0F,0x01,0x01,0x07,0x3F,
    0xFF,0xFF,0xF8,0xC0,0x00,0x00,0x00,0xF8,0xF8,0xF8,0xB8,0xB8,0xB8,0xB8,0xF8,0xF8,
    0xF0,0xF8,0xFE,0xFF,0xFF,0xCF,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,
    0xFF,0xFF,0xFF,0x0F,0x3F,0x7E,0xFC,0xF0,0xE0,0x80,0x00,0x00,0xC0,0xF0,0xFC,0xFF,
    0x3F,0x0F,0x03,0x01,0x07,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0xF0,0xFC,0xFF,0x7F,0x1F,0x0F,0x0F,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,
    0x0E,0x0F,0x1F,0xFF,0xFF,0xF8,0xE0,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
    0x01,0x01,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,
    0x03,0xFF,0xFF,0xFF,0x80,0x00,0x01,0x07,0x0F,0x1F,0x1F,0x1F,0x0F,0x07,0x03,0x00,
    0x00,0x00,0x00,0x00,0x00,0x03,0x1F,0xFF,0xFF,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x0F,0x0F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x03,0x1F,0x3F,0x3F,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x3F,0x3F,0x3F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x80,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0xFC,
    0xFC,0xFC,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,0xC0,0xC0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x80,0xC0,
    0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x01,0x7F,0xFF,0xFF,0xF0,
    0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
    0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,
    0xE3,0xF9,0xF8,0xB8,0xBC,0xBC,0xBF,0x9F,0x9F,0x8F,0x00,0x00,0xFC,0xFF,0xFF,0xCF,
    0x83,0x81,0x01,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
    0xFF,0x3F,0x0F,0x03,0x03,0x03,0x07,0x1F,0xFF,0xFE,0xF8,0xC0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
    0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
    0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x03,0x03,0x07,
    0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x07,
    0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
*/
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting OLED i2c Test");
  beginOLED();
  displayFrame();
  //delay(1000);
  //sendCommand(DISPLAYOFF);
  delay(1000);
  drawPixel(3, 40, 1);
  displayFrame();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Wire.beginTransmission(I2CADDR);
  
}


