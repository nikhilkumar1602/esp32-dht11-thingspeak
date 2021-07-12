#include <DHT.h> //  DHT.h library
#include <WiFi.h> // ESP8266WiFi.h library
#include <HTTPClient.h>
#define DHTPIN 16
#define DHTTYPE  DHT11

const char* ssid     = "My Zone";
const char* password = "sreevani";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "9GHWISDCEIZON1J7";

DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {

  Serial.begin(115200);
  dht.begin();
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
    
  }
}

void loop() {
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    return;
  }


  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
   Serial.print("Temperature: ");
   Serial.print(temperature);
   Serial.print(" degrees Celcius, Humidity: ");
   Serial.print(humidity);
   Serial.println("%. Sent to Thingspeak.");
  
  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temperature);
  url+="&field2=";
  url+=String(humidity);
  url+="\r\n";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(5000);
}
