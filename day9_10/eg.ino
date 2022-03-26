#include "WiFi.h"
#include "ThingSpeak.h"
#include  "HTTPClient.h"

char ssid[] = "Kk";
char pass[] = "itirk@229";
  bool checkPoint = true;
const int PIN_LED=22;
const int PIN_PIR=2;
const int PIN_TRIG=5;
const int PIN_ECHO=18;
const int PIN_BUZZER=21;
int val=0;
long duration;
float distanceCm;


//----ThingSpeak Details----//

unsigned long myChannelField = 1653488;
const int ChannelField1 = 1;
//const int ChannelField2 = 2;
const char * myWriteAPIKey = "MKON9ZIXT3UKS1UU";
#define SOUND_SPEED 0.034


WiFiClient client;

void setup() {
 Serial.begin(115200);
 pinMode(PIN_LED,OUTPUT);
 pinMode(PIN_PIR,INPUT);
 pinMode(PIN_TRIG,OUTPUT);
 pinMode(PIN_ECHO,INPUT);
 pinMode(PIN_BUZZER,OUTPUT);
 WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);

}

void loop()
 {
   if(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("Attempting to Connect to SSID: ");
    Serial.println(ssid);

    while(WiFi.status()!=WL_CONNECTED)
    {
      WiFi.begin(ssid,pass);
    Serial.print(".");
    delay(5000);
    }
    Serial.println("\nConnected");
  }
  
   //check the human present
  val =  digitalRead(PIN_PIR);
  Serial.println(val);
  if(val==1) //if human present LED glows
  {
    digitalWrite(PIN_LED,HIGH);
    Serial.println("Human detected!\n");
   digitalWrite(PIN_TRIG, LOW);
    delay(1);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO,HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  distanceCm = duration * SOUND_SPEED/2; // Calculate the distance
    // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): \n");
  Serial.println(distanceCm);
  
    if(distanceCm<=100)
    { 
      Serial.print("Buzzer on------->Human has crossed threshold value\n");
      digitalWrite(PIN_BUZZER,HIGH);
     
     }
       // Serial.println(count+1);
        ThingSpeak.writeField(myChannelField, ChannelField1,distanceCm, myWriteAPIKey);
    }
 
  else
  {
    Serial.println("No Human detected!\n");
    if(checkPoint)
      {
        HTTPClient http;
        Serial.println("HTTP Begin...\n");

        http.begin("https://api.thingspeak.com/apps/thinghttp/send_request?api_key=RM4NJJ0T0BZ0AOAO&message=");
        
        Serial.print("HTTP GET......\n");
        int httpCode =http.GET();
        if(httpCode >0)
        {
          Serial.print("HTTP GET......\n");
          String payload =http.getString();
          Serial.println(payload);
          checkPoint= false;
        }

      }
}
 }