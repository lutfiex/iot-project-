#include <Wire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define DHTPIN 4
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);


int i;
void setup(){
  Serial.begin(115200);
  Wire.begin(2,0);
  dht.begin();
 lcd.begin(20,4);
  lcd.backlight(); // Enable or Turn On the backlight 
dht.begin();
  lcd.setBacklight(HIGH);
  delay(1000);
  WiFi.begin("lut", "ceku9562");

while (WiFi.status() != WL_CONNECTED) {
 lcd.print("Connecting...");
delay(1000);
Serial.println("Connecting..");

lcd.clear();
}
Serial.println("Connected");
lcd.print("Connected");
delay(1000);
}
  

 
void loop()
{
  if(i> 20){
    i = 0;
    }
  if (WiFi.status() == WL_CONNECTED){
  HTTPClient http;
  float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  delay(5000); 
  lcd.home();
  String suhu = String(t); 
String huma = String(h);

  Serial.print(suhu);
Serial.print(" ");
Serial.println(huma);
  lcd.clear();
  lcd.setCursor(i,2);
  lcd.print("dev: Lutfi & Jefri");
  lcd.setCursor(0,0);
  lcd.print("humidity: ");
  lcd.print(huma);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("temperature: ");
  lcd.print(suhu);
  lcd.print(" C");

 i++;
  

String hasil = "ard/as.php?udara=" + suhu + "&kelembapan=" + huma + "&submit=Submit";
String Link = "http://192.168.43.59/" + hasil ;
http.begin(Link);
int httpCode = http.GET();  
String payload = http.getString();
Serial.println(Link);
http.end();
  // Nothing Absolutely Nothing!
}
}
