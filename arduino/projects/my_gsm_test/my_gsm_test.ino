/*
 * Description: My test code
 * Date Created: 18 Jul 2017
 * Date Modified: 18 Jul 2017
 * Author: Andrey Miroshnikov
 */
/*
#include "sim800lib.h"
#include <SoftwareSerial.h>
//Declarations
Sim800l TestSim; //Creates sim 800l class
String msgText;
uint8_t msgIndex;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Testing Testing");
  TestSim.begin();
  msgIndex = 3;
  msgText = TestSim.readSms(msgIndex);
  Serial.println(msgText);
  //Serial.println("Starting");
  //TestSim.reset();
  //TestSim.setPhoneFunctionality();
  //Serial.println("Signal");
  //TestSim.signalQuality();
  //Serial.println("Calling");
  //TestSim.callNumber("+123456789");
  //TestSim.dateNet();
}

void loop() {
  // put your main code here, to run repeatedly:
  TestSim.answerCall();
}
*/
#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 12
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 11
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //pinMode(2, OUTPUT);
  //digitalWrite(2, HIGH);
  //delay(1000);
  //digitalWrite(2, LOW);
  //while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
}
 
void loop() {
  //Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM800.available()){
    Serial.write(serialSIM800.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  if(Serial.available()){    
    serialSIM800.write(Serial.read());
  }
}
