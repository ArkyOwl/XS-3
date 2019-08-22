/*
Program description: Test Keypad (only 14 keys) test program. Not enough keys really.
Author: Andrey Miroshnikov
Date Created: 22/07/12017
Last Updated: 22/07/12017
*/
#include <Keypad.h>

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
String keyInput;
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int indexLastChar = 0;
void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if (customKey=='*'){
    Serial.println(keyInput);
    Serial.println("Length of buffer: "+String(keyInput.length()));
  }
  if (customKey == '-'){
    indexLastChar = keyInput.length()-1;
    keyInput.remove(indexLastChar);
  }
  if (customKey && customKey != '*' && customKey != '-'){
    keyInput += customKey;
  }
}
