/*
Program description: Test program that joins the OLED, keypad and SIM800L module in one system!
Author: Andrey Miroshnikov
Date Created: 22/07/12017
Last Updated: 22/07/12017
*/

//------------------------------------------Includes
#include <Keypad.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SoftwareSerial.h>
//------------------------------------------Declarations
//Keypad
const byte ROWS = 5; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'+',' ','-'},
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad
char buf[13]; //input buffer
int bufIndex = 0;
boolean controlCharFlag = false; //indicates whether control key was pressed that shouldn't be printed to OLED/Serial
//OLED
#define OLED_RESET 4
String batteryLevel = "56";
String rssiLevel = "20";
//SIM800
#define SIM800_TX_PIN 12
#define SIM800_RX_PIN 11
char toSend[24];

//------------------------------------------Class instantiation
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Adafruit_SSD1306 display(OLED_RESET);
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//------------------------------------------Setup
void setup(){
  Serial.begin(9600);//For testing
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("-"+RSSItoDBM(rssiLevel)+"dBm");
  display.setCursor(64,0);
  display.print(batteryLevel+"%");
  display.println(" ");
  display.println("Please enter number:");
  display.display();

  serialSIM800.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
}
//------------------------------------------Main loop
void loop(){
  char customKey = customKeypad.getKey();
  controlCharFlag = ((customKey == '+') || (customKey == '*') || (customKey == '-') || customKey == ('#'));
  if (customKey=='+'){
    display.println(" ");
    display.println("Calling number");
    display.display();
    //Code for ATD command
    sprintf(toSend,"ATD+%s;\n", buf);
    serialSIM800.write(toSend);
  }
  if (customKey=='*'){
    Serial.println(buf);
    Serial.println("Length of buffer: "+String(sizeof(buf)));
    serialSIM800.write("AT\n");
  }
  if (customKey == '-'){
    if(bufIndex-1 < 0)
    {
      Serial.println("No numbers stored!!!");
    }
    else
    {
      strncpy(buf, buf, bufIndex);
      bufIndex--;
      Serial.println(bufIndex);
      redrawOLED();
    }
  }
  if (customKey == '#'){
  }
  if (customKey && !controlCharFlag){
    if ((bufIndex+1) == sizeof(buf))
    {
      Serial.println("Cannot input anymore characters!!");
    }
    else
    {
      buf[bufIndex] = customKey;
      bufIndex++;
      Serial.println(bufIndex);
      //Print to OLED here
    display.print(customKey);
    display.display();
    }
  }
  //Debugging SIM800
  if(serialSIM800.available()){
    Serial.write(serialSIM800.read());
  }
}

//------------------------------------------Function declaration
/*
 * Function for converting RSSI values to dBm (for more geeky display ;) )
 */
String RSSItoDBM(String rssiStrength)
{
  int result = rssiStrength.toInt();
  result = 113 - (2*result);
  return String(result);
}
/*
 * Redraw screen
 */
void redrawOLED()
{
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("-"+RSSItoDBM(rssiLevel)+"dBm");
  display.setCursor(64,0);
  display.print(batteryLevel+"%");
  display.println(" ");
  display.println("Please enter number:");
  display.print(buf);
  display.display();
}

