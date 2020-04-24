
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

#define FIREBASE_HOST "firebase_host"
#define FIREBASE_AUTH "FIREBASE_AUTH"
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "WIFI_PASSWORD"
float Irms;
//Define FirebaseESP8266 data object
FirebaseData firebaseData;
String path = "/nilai/Data";
String jsonStr;
void setup()
{

  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  

  Serial.println("-----------------------------------");
  Serial.println("----------Begin Set Test-----------");
  Serial.println("-----------------------------------");
  Serial.println();

 
emon1.current(0, 70); 
  

  
}

void loop()
{
  
  float incomingByte = Serial.read();
  if (Firebase.setFloat(firebaseData, path , incomingByte))
    {
      
      Serial.print("VALUE: ");
      Serial.println(incomingByte);
    }
    else
    {
      Serial.println("----------Can't set data--------");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("--------------------------------");
      Serial.println();
    }
    
}
