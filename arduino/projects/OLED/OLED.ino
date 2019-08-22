/*
Program description: OLED Test program.
Author: Andrey Miroshnikov
Date Created: 22/07/12017
Last Updated: 22/07/12017
*/

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

String batteryLevel = "56";
String rssiLevel = "20";

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("-"+RSSItoDBM(rssiLevel)+"dBm");
  display.setCursor(64,0);
  display.print(batteryLevel+"%");
  display.display();
  delay(2000);
  
}


void loop() {
  
}
/*
 * Function for converting RSSI values to dBm (for more geeky display ;) )
 */
String RSSItoDBM(String rssiStrength)
{
  int result = rssiStrength.toInt();
  result = 113 - (2*result);
  return String(result);
}
