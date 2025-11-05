#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "..........";
const char* password = ".........";
String apiKey = "...............";  
const char* server = "http://api.thingspeak.com/update";
const int gasPin = 34;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int gasValue = analogRead(gasPin); 
    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(gasValue);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent successfully!");
    } else {
      Serial.println("Error sending data.");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
  delay(15000);  
}
