/*#include "ThingSpeak.h"
#include "WiFi.h"
//#include <Wire.h>  //Include Library for HTU21D
//#include "SparkFunHTU21D.h"

//-------Enter your WiFi Details------//
char ssid[] = "JioFi2_056F1B";  //SSID
char pass[] = "6xk39nuzyy";  //Password
//-----------------------------------//
//"JioFi2_056F1B"
//psk="6xk39nuzyy"
WiFiClient client;

//-------------ThingSpeak Details-----------------//
unsigned long myChannelField = 1645354; //Channel ID
const int ChannelField1 = 1; //for Humidity
const int ChannelField2 = 2; //for Temperature
const char * myWriteAPIKey = "XVCTSBNKEEP8ZZI0"; //Your Write API Key
//-----------------------------------------------//*/
const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //WiFi.mode(WIFI_STA);
 // ThingSpeak.begin(client);
}

void loop() {
   //-----------------WiFi Setup-------------------//
 /* if(WiFi.status()!= WL_CONNECTED)
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
  Serial.println("\nConnected.");*/
  //--------------------------------------------//
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(100);
  
  /*//-------------Sending Data to ThingSpeak Cloud---------------//
  ThingSpeak.writeField(myChannelField,ChannelField1,distanceCm, myWriteAPIKey);
  ThingSpeak.writeField(myChannelField,ChannelField2, distanceInch, myWriteAPIKey);*/
}
