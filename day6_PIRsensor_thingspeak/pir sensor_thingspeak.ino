#include "ThingSpeak.h"
#include "WiFi.h"

/*
 * PIR sensor tester
 */
int ledPin = 13; // choose the pin for the LED
int inputPin = 2; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
//-------Enter your WiFi Details------//
char ssid[] = "Kk";  //SSID
char pass[] = "itirk@229";  //Password
//-----------------------------------//
//"JioFi2_056F1B"
//psk="6xk39nuzyy"
WiFiClient client;

//-------------ThingSpeak Details-----------------//
unsigned long myChannelField = 1646253; //Channel ID
const int ChannelField1 = 1; //for Humidity
const int ChannelField2 = 2; //for Temperature
const char * myWriteAPIKey = "8T14CL1BOU2W1YST"; //Your Write API Key
//-----------------------------------------------//
void setup() {

Serial.begin(115200);
 pinMode(ledPin, OUTPUT); // declare LED as output
 pinMode(inputPin, INPUT); // declare sensor as input
 WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop(){
  //-----------------WiFi Setup-------------------//
  if(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("Attempting to Connect to SSID: ");
    Serial.println(ssid);
  }
  while(WiFi.status()!= WL_CONNECTED)
  {
    WiFi.begin(ssid,pass);
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("\nConnected.");
 val = digitalRead(inputPin); // read input value
 if (val == HIGH) { // check if the input is HIGH
 digitalWrite(ledPin, HIGH); // turn LED ON
 if (pirState == LOW) {
 // we have just turned on
 Serial.println("Motion detected!");
 // We only want to print on the output change, not state
 pirState = HIGH;
 }
 } else {
 digitalWrite(ledPin, LOW); // turn LED OFF
 if (pirState == HIGH){
 // we have just turned of
 Serial.println("Motion ended!");
 // We only want to print on the output change, not state
 pirState = LOW;
 }
 }
 
  //-------------Sending Data to ThingSpeak Cloud---------------//
  ThingSpeak.writeField(myChannelField,ChannelField1,ledPin, myWriteAPIKey);
  ThingSpeak.writeField(myChannelField,ChannelField2, inputPin, myWriteAPIKey);
}