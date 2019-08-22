/*
Program description: Test program that joins the OLED, keypad and SIM800L module in one system!
Author: Andrey Miroshnikov
Date Created: 22/07/12017
Last Updated: 25/07/12017
Updates: Replaced the provided SS1306 library and the standard Wire lib - More RAM :)
*/

//------------------------------------------Includes
#include <Keypad.h>
//More efficient versions!
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

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
char bufCopy[13];
int bufIndex = 0;
boolean controlCharFlag = false; //indicates whether control key was pressed that shouldn't be printed to OLED/Serial
boolean calling = false;
//OLED
#define I2C_ADDRESS 0x3C
char battLevel[3] = "56";
char rssiLevel[3] = "20";
char topLine[22];
//char number[13];
char numLine[14];
//SIM800
#define SIM800_TX_PIN 12
#define SIM800_RX_PIN 11
char toSend[24];

//------------------------------------------Class instantiation
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
SSD1306AsciiAvrI2c Oled;
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//------------------------------------------Setup
void setup(){
  Serial.begin(9600);//For testing
  //Convert RSSI to dBm and sprintf the thing
  RSSItoDBM(rssiLevel, rssiLevel);
  sprintf(topLine, "Sig: -%sdBm Batt: %s%%", rssiLevel, battLevel); 
  //Initialise OLED library
  Oled.begin(&Adafruit128x64, I2C_ADDRESS);
  Oled.setFont(Adafruit5x7);
  //Clear and print default
  Oled.clear();  
  Oled.println(topLine);
  Oled.println("Enter number:");
  sprintf(numLine, "+%s", buf);
  Oled.println("");
  Oled.print(buf);
  //SIM800L
  serialSIM800.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
}
//------------------------------------------Main loop
void loop(){
  char customKey = customKeypad.getKey();
  controlCharFlag = ((customKey == '+') || (customKey == '*') || (customKey == '-') || customKey == ('#'));
  if (customKey=='+'){
    Oled.println("");
    Oled.println("Calling number");
    //Code for ATD command
    sprintf(toSend,"ATD+%s;\n", buf);
    serialSIM800.write(toSend);
    calling = true;
  }
  if (customKey=='*'){
    Serial.println(buf);
    Serial.println("Length of buffer: "+String(sizeof(buf)));
    serialSIM800.write("AT\n");
  }
  if (customKey == '-'){
    if(calling)
    {
      serialSIM800.write("ATH\n");
      calling = false;
    }
    if(bufIndex-1 < 0)
    {
      Serial.println("No numbers stored!!!");
    }
    else
    {
      bufIndex--;
      //strncpy(bufCopy, buf, bufIndex);
      buf[bufIndex] = '\0';
      Serial.println(buf);
      Serial.println(bufIndex);
      redrawOLED();
    }
  }
  if (customKey == '#'){
    serialSIM800.write("ATA\n");
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
    Oled.print(customKey);
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
void RSSItoDBM(char *rssiStrength, char *dBmResult)
{
  //Convert RSSI string to an int
  int result = atoi(rssiStrength);
  //Use linear relation to convert to dBm
  result = 113 - (2*result);
  //Convert result to string using low level sprintf
  sprintf(dBmResult, "%d", result);
}
/*
 * Redraw screen
 */
void redrawOLED()
{
  Oled.clear();  
  Oled.println(topLine);
  Oled.println("Enter number:");
  sprintf(numLine, "+%s", buf);
  Oled.println("");
  Oled.print(buf);
}

